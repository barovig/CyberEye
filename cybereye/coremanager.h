#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H
#include "opencv2/opencv.hpp"
//#include "opencv2/videoio.hpp"
#include "engine.h"
#include "tracker.h"
#include "collector.h"

namespace ce {

class CoreManager
{
private:
	Engine* _engine;
	Collector* _collector;
    Tracker* _tracker;
    cv::VideoCapture _vcap;
    cv::Mat _frame;

    void capture();
public:
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker);
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker, int vcap);
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker, cv::VideoCapture vcap);
	cv::Mat getFrame();
    void startCapture();
};


} // namespace ce
#endif // CE_COREMANAGER_H
