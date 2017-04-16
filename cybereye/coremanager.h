#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "engine.h"
#include "tracker.h"
#include "collector.h"
#include "collection.h"
#include "recognitionengine.h"
#include "receiver.h"
#include <atomic>
#include <set>
#include <thread>
#include <chrono>
#include <iostream>

namespace ce {

/**
 * @brief The CoreManager class.
 */
class CoreManager
{
	
	
private:
	// Core elements
	cv::Ptr<Engine>				_engine;
	cv::Ptr<Collector>			_collector;
	cv::Ptr<Tracker>			_tracker;
	cv::Ptr<RecognitionEngine>	_recengine;
	cv::Ptr<Receiver>			_receiver;
	cv::Ptr<Collection>			_model;
	cv::VideoCapture			_vcap;
	cv::Mat						_frame;
		
	// flags and configs
	std::atomic_bool _vcap_stop {false};	// note the use of initialiser instead of operator=
	std::atomic_bool _engine_stop {false};
	std::atomic_bool _collector_stop {false};
	std::atomic_bool _tracker_stop {false};
	std::atomic_bool _recengine_stop {false};
	std::atomic_bool _receiver_stop {false};

	int				 _engine_wait_ms;
	int				 _stop_thread_wait_ms = 500; //wait half-second for threads to finish			
	int				 _feature_thres = 3;
	std::set<int>	 _monitor_ids;
	std::mutex		 _tm_lock;	// tracker/montor lock
	
	// thread procedures
	void capture();
	void segment();
	void track();
	void collect();
	void monitor();
	void receive();
	
	// helpers
	void segmentOnce();
	
public:
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model);
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model, int vcap);
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model, cv::VideoCapture vcap);
	~CoreManager();
	
	void setFeatureThreshold(int thres);
	void setReceiver(cv::Ptr<Receiver> recv);
	void getFrame(cv::Mat& frame);
	void startCapture();
	void startSegmentation();
	void startTracking();
	void startMonitoring();
	void startReceiving();
	void triggerSegmentation();	
	void stopAllThreads();
	
};


} // namespace ce
#endif // CE_COREMANAGER_H
