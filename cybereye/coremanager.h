#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "engine.h"
#include "tracker.h"
#include "collector.h"

namespace ce {

const int DEFAULT_ENGINE_TIMEOUT = 50;

class CoreManager
{
private:
	Engine* _engine;
	Collector* _collector;
    Tracker* _tracker;
    cv::VideoCapture _vcap;
    cv::Mat _frame;
	int		_engine_wait_ms = 10;

    void capture();
	void segment();
	void segmentOnce();
	
public:
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker);
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker, int vcap);
    CoreManager(Engine* engine, Collector* collector, Tracker* tracker, cv::VideoCapture vcap);
	
	cv::Mat getFrame();
    void startCapture();
	void startSegmentation(int wait = DEFAULT_ENGINE_TIMEOUT);
	void triggerSegmentation();
	void setEngineWait(int wait);
};


} // namespace ce
#endif // CE_COREMANAGER_H
