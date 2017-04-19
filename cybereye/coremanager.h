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
 * @brief The CoreManager class. This is the main orchestrator class which controls all individual components and
 * manages working threads. Does not control lifetime of components. 
 * Can be used directly by the client or via CyberEye class abstraction.
 */
class CoreManager
{
private:
	// Core elements - smart pointers to components
	cv::Ptr<Engine>				_engine;
	cv::Ptr<Collector>			_collector;
	cv::Ptr<Tracker>			_tracker;
	cv::Ptr<RecognitionEngine>	_recengine;
	cv::Ptr<Receiver>			_receiver;
	
	// Central collection
	cv::Ptr<Collection>			_model;
	
	// cv::VideoCapture object
	cv::VideoCapture			_vcap;
	
	// Holds last extracted video frame
	cv::Mat						_frame;
		
	// Thread control atomic flags
	std::atomic_bool _vcap_stop {false};	// note the use of initialiser instead of operator=
	std::atomic_bool _engine_stop {false};
	std::atomic_bool _collector_stop {false};
	std::atomic_bool _tracker_stop {false};
	std::atomic_bool _recengine_stop {false};
	std::atomic_bool _receiver_stop {false};

	// Misc config values
	int				 _engine_wait_ms;			 // wait time for segmentation engine
	int				 _stop_thread_wait_ms = 500; // wait half-second for ALL threads to finish
	
	// number of detected features, below which object is considered gone from frame
	int				 _feature_thres = 3;
	
	// IDs of objects that are being monitored, used to detect new objects
	std::set<int>	 _monitor_ids;
	
	// tracker/monitor lock
	std::mutex		 _tm_lock;	
	
	// Core thread procedures
	void capture();
	void segment();
	void track();
	void collect();
	void monitor();
	void receive();
	
	// helpers
	void segmentOnce();
	
public:
	/**
	 * @brief CoreManager constructor
	 * @param engine Smart pointer to instance of Engine.
	 * @param collector Smart pointer to instance of Collector.
	 * @param tracker Smart pointer to instance of Tracker.
	 * @param recengine Smart pointer to instance of RecognitionEngine.
	 * @param model Smart pointer to instance of Collection.
	 */
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model);
	/**
	 * @brief CoreManager constructor
	 * @param engine Smart pointer to instance of Engine.
	 * @param collector Smart pointer to instance of Collector.
	 * @param tracker Smart pointer to instance of Tracker.
	 * @param recengine Smart pointer to instance of RecognitionEngine.
	 * @param model Smart pointer to instance of Collection.
	 * @param vcap Index of video capturing device.
	 */
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model, int vcap);
	/**
	 * @brief CoreManager constructor.
	 * @brief CoreManager constructor
	 * @param engine Smart pointer to instance of Engine.
	 * @param collector Smart pointer to instance of Collector.
	 * @param tracker Smart pointer to instance of Tracker.
	 * @param recengine Smart pointer to instance of RecognitionEngine.
	 * @param model Smart pointer to instance of Collection.
	 * @param vcap cv::VideoCapture device to use.
	 */
	CoreManager(cv::Ptr<Engine> engine, cv::Ptr<Collector> collector, cv::Ptr<Tracker> tracker, 
				cv::Ptr<RecognitionEngine> recengine, cv::Ptr<Collection> model, cv::VideoCapture vcap);
	/**
	 * @brief CoreManager constructor used on the recognition server.
	 * @param receiver Smart pointer to instance of Receiver.
	 * @param engine Smart pointer to instance of RecognitionEngine.
	 */
	CoreManager(cv::Ptr<Receiver> receiver, cv::Ptr<RecognitionEngine> engine);
	
	~CoreManager();
	/**
	 * @brief Sets the minimum number of features detected for given object to be considered present on a scene.
	 * @param thres Integer minimum number of features.
	 */
	void setFeatureThreshold(int thres);
	/**
	 * @brief Explicitly sets the Receiver object to be used.
	 * @param recv Smart pointer to Receiver instance.
	 */
	void setReceiver(cv::Ptr<Receiver> recv);
	/**
	 * @brief Sets parameter to a copy of frame with all objects surrounded by bounding boxes and with labels (if present). Main output procedure.
	 * @param frame Reference to cv::Mat which will be populated with processed image data.
	 */
	void getFrame(cv::Mat& frame);
	/**
	 * @brief Starts video capturing thread.
	 */
	void startCapture();
	/**
	 * @brief Starts image segmentation thread.
	 */
	void startSegmentation();
	/**
	 * @brief Starts object tracking thread.
	 */
	void startTracking();
	/**
	 * @brief Starts a thread that monitors central Collection for changes.
	 */
	void startMonitoring();
	/**
	 * @brief Starts synchrounous procedure in Receiver which will listen for incoming data until stopped.
	 */
	void startReceiving();
	/**
	 * @brief Performs image segmentation on current frame once.
	 */
	void triggerSegmentation();
	/**
	 * @brief Clears underlying central ImgObj collection.
	 */
	void clearModel();
	/**
	 * @brief Stops all running threads.
	 */
	void stopAllThreads();
	
};


} // namespace ce
#endif // CE_COREMANAGER_H
