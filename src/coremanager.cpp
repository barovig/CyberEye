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
	while(!_engine_stop.load())
	{
		if(!_frame.empty())
		{
			// Need a local copy, since _frame can be updated by
			// video capturing thread
			cv::Mat frame;
			_frame.copyTo(frame);
			_engine->fillImgObjects(frame);
			std::this_thread::sleep_for(std::chrono::milliseconds(wait));
		}
	}
}

void CoreManager::segmentOnce()
{
	if(!_frame.empty())	
		_engine->fillImgObjects(_frame);
}

CoreManager::CoreManager(Engine* e, Collector* c, Tracker* t) :
	_engine{e}, _collector{c}, _tracker{t},
	_vcap{cv::VideoCapture(0)}
{
}


CoreManager::CoreManager(Engine* e, Collector* c, Tracker* t, int vcap) :
	_engine {e}, _collector {c}, _tracker {t},
	_vcap {cv::VideoCapture(vcap)}
{
}


CoreManager::CoreManager(Engine* e, Collector* c, Tracker* t, cv::VideoCapture vcap) :
	_engine {e}, _collector {c}, _tracker {t},
	_vcap {vcap}
{
}

CoreManager::~CoreManager()
{
	stopAllThreads();
}

cv::Mat CoreManager::getFrame()
{
    return _collector->getCurrentFrame(_frame);
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
	std::thread t(&CoreManager::segment, this);
	t.detach();	
}

void CoreManager::triggerSegmentation()
{
	std::thread t(&CoreManager::segmentOnce, this);
	t.detach();
}

void CoreManager::stopAllThreads()
{
	_engine_stop.store(true);
	_vcap_stop.store(true);
	_collector_stop.store(true);
	_tracker_stop.store(true);
	
	// give engine a chance to stop
	std::this_thread::sleep_for(std::chrono::milliseconds(_engine->getEngineWait()*2));
}

} // namespace ce
