#include <thread>

#include "coremanager.h"
#include "opencv/cv.h"

namespace ce {

void CoreManager::capture()
{
    while(true)
        _frame = _vcap.grab();
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
    //return _collector->getCurrentFrame(_frame);
    return _frame;
}

void CoreManager::startCapture()
{
    std::thread t(&CoreManager::capture, this);
    t.detach();
}

} // namespace ce
