#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "engine.h"
#include "tracker.h"
#include "collector.h"
#include "collection.h"
#include <atomic>

namespace ce {

const int DEFAULT_ENGINE_TIMEOUT = 50;

class CoreManager
{
private:
	// Core elements
	cv::Ptr<Engine>		_engine;
	cv::Ptr<Collector>	_collector;
	cv::Ptr<Tracker>	_tracker;
	cv::VideoCapture	_vcap;
	cv::Mat				_frame;
	
	//std::atomic<cv::Mat> _frame;
	
	// flags and configs
	std::atomic_bool _vcap_stop {false};	// note the use of initialiser instead of operator=
	std::atomic_bool _engine_stop {false};
	std::atomic_bool _collector_stop {false};
	std::atomic_bool _tracker_stop {false};
	int				 _engine_wait;			// engine might be deallocated, don't rely on getEngineWait()
	
	// thread procedures
	void capture();
	void segment();
	
	// helpers
	void segmentOnce();
	
public:
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker);
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, int vcap);
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, cv::VideoCapture vcap);
	~CoreManager();
	
	void getFrame(cv::Mat& frame);
	void startCapture();
	void startSegmentation();
	void startTracking();
	void triggerSegmentation();	
	void stopAllThreads();
	
};


} // namespace ce
#endif // CE_COREMANAGER_H
