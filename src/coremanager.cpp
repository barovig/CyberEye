#include <thread>
#include <chrono>
#include <iostream>

#include "coremanager.h"
#include "opencv/cv.h"
 
namespace ce {

void CoreManager::capture()
{
    while(!_vcap_stop.load())
		_vcap.read(_frame);
}

void CoreManager::segment()
{
	int wait = _engine->getEngineWait();
	// if wait is zero - this is supervised segmenetation engine
	if(wait == 0) return;
	
	while(!_engine_stop.load())
	{
		if(!_frame.empty())
		{
			// Need a local copy, since _frame can be updated by
			// video capturing thread
			cv::Mat frame = _frame.clone();
			_engine->segment(frame);
			std::this_thread::sleep_for(std::chrono::milliseconds(wait));
		}
	}
}

void CoreManager::track()
{
	while(!_tracker_stop.load())
	{
		if(!_frame.empty())
		{
			_tracker->track(_frame);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			
		}
	}
}

void CoreManager::segmentOnce()
{
	if(!_frame.empty())	
		_engine->segment(_frame);
}

CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t) :
	_engine{e}, _collector{c}, _tracker{t},
	_vcap{cv::VideoCapture(0)}
{
	_engine_wait_ms = e->getEngineWait();
}


CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t, int vcap) :
	_engine {e}, _collector {c}, _tracker {t},
	_vcap {cv::VideoCapture(vcap)}
{
	_engine_wait_ms = e->getEngineWait();
}


CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t, cv::VideoCapture vcap) :
	_engine {e}, _collector {c}, _tracker {t},
	_vcap {vcap}
{
	_engine_wait_ms = e->getEngineWait();
}

CoreManager::~CoreManager()
{
//	stopAllThreads();
}

void CoreManager::getFrame(cv::Mat& frame)
{
	// create local copy of current frame, before passing to Collector
	const cv::Mat localFrame = _frame.clone();
    _collector->getFrame(localFrame, frame);
}

void CoreManager::startCapture()
{
	if(_vcap.isOpened()){
		_vcap_stop.store(false);
		std::thread t(&CoreManager::capture, this);
		t.detach();
	}
	else
	{
		std::cerr << "VideoCapture is closed" << std::endl;
	}
}

void CoreManager::startSegmentation()
{
	_engine_stop.store(false);

	_engine->setMaxObjectArea((_frame.rows * _frame.cols) * 0.9);
	std::thread t(&CoreManager::segment, this);
	t.detach();	
}

void CoreManager::startTracking()
{
	_tracker_stop.store(false);

	std::thread t(&CoreManager::track, this);
	t.detach();
}

void CoreManager::triggerSegmentation()
{
	if(!_frame.empty())	// don't segment if no frames acquired
	{
		_engine->setMaxObjectArea((_frame.rows * _frame.cols) * 0.9);
		std::thread t(&CoreManager::segmentOnce, this);
		t.detach();
	}
}

void CoreManager::stopAllThreads()
{
	if(!(_engine_stop.load() && 
		 _vcap_stop.load() && 
		 _collector_stop.load() &&
		 _tracker_stop.load()))
	{
		_engine_stop.store(true);
		_vcap_stop.store(true);
		_collector_stop.store(true);
		_tracker_stop.store(true);
		
		// give engine a chance to stop (sum of preset wait + engine wait)
		std::this_thread::sleep_for(std::chrono::milliseconds(_stop_thread_wait_ms+_engine_wait_ms));
	}
}

} // namespace ce
