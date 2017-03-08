#include <thread>
#include <chrono>

#include "coremanager.h"
#include "opencv/cv.h"
 
namespace ce {

void CoreManager::capture()
{
    while(true)
		_vcap.read(_frame);
}

void CoreManager::segment()
{
	while(true)
	{
		_engine->fillImgObjects(_frame);
		std::this_thread::sleep_for(std::chrono::milliseconds(_engine_wait_ms));
	}
}

void CoreManager::segmentOnce()
{
	_engine->fillImgObjects(_frame);
}

CoreManager::CoreManager(Engine* engine, Collector* collector, Tracker* tracker)
{
    _engine = engine;
    _collector = collector;
    _tracker = tracker;
    _vcap = cv::VideoCapture(0);
}


CoreManager::CoreManager(Engine* engine, Collector* collector, Tracker* tracker, int vcap)
{
    _engine = engine;
    _collector = collector;
    _tracker = tracker;
    _vcap = cv::VideoCapture(vcap);
}


CoreManager::CoreManager(Engine* engine, Collector* collector, Tracker* tracker, cv::VideoCapture vcap)
{
    _engine = engine;
    _collector = collector;
    _tracker = tracker;
    _vcap = vcap;
}

cv::Mat CoreManager::getFrame()
{
    return _collector->getCurrentFrame(_frame);
}

void CoreManager::startCapture()
{
	std::thread t(&CoreManager::capture, this);
	t.detach();
}

void CoreManager::startSegmentation(int wait)
{
	setEngineWait(wait);
	std::thread t(&CoreManager::segment, this);
	t.detach();	
}

void CoreManager::triggerSegmentation()
{
	std::thread t(&CoreManager::segmentOnce, this);
}

void CoreManager::setEngineWait(int wait_ms)
{
	_engine_wait_ms = wait_ms;
}

} // namespace ce
