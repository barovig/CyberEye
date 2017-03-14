#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "engine.h"
#include "tracker.h"
#include "collector.h"
#include <atomic>

namespace ce {

const int DEFAULT_ENGINE_TIMEOUT = 50;

class CoreManager
{
private:
	// Core elements
	cv::Ptr<Engine> _engine;
	cv::Ptr<Collector> _collector;
	cv::Ptr<Tracker> _tracker;
	cv::VideoCapture _vcap;
	cv::Mat _frame;
	//std::atomic<cv::Mat> _frame;
	
	// flags and configs
	int _engine_wait_ms = 10;
	std::atomic_bool _vcap_stop {false};	// note the use of initialiser instead of operator=
	std::atomic_bool _engine_stop {false};
	std::atomic_bool _collector_stop {false};
	std::atomic_bool _tracker_stop {false};
	
	// thread procedures
	void capture();
	void segment();
	
	// helpers
	void segmentOnce();
	
public:
	CoreManager(Engine* engine, Collector* collector, Tracker* tracker);
	CoreManager(Engine* engine, Collector* collector, Tracker* tracker, int vcap);
	CoreManager(Engine* engine, Collector* collector, Tracker* tracker, cv::VideoCapture vcap);
	~CoreManager();
	
	cv::Mat getFrame();
	void startCapture();
	void startSegmentation(int wait = DEFAULT_ENGINE_TIMEOUT);
	void triggerSegmentation();
	void setEngineWait(int wait);
	
	void stopAllThreads();
	
};


} // namespace ce
#endif // CE_COREMANAGER_H
