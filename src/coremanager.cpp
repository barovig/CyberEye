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
			_tm_lock.lock();
			_tracker->track(_frame);
			_tm_lock.unlock();
//			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			
		}
	}
}

void CoreManager::segmentOnce()
{
	if(!_frame.empty())	
		_engine->segment(_frame);
}

CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t, cv::Ptr<RecognitionEngine> r, cv::Ptr<Collection> m) :
	_engine{e}, _collector{c}, _tracker{t}, _recengine{r}, _model{m},
	_vcap{cv::VideoCapture(0)}
{
	_engine_wait_ms = e->getEngineWait();
}


CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t, cv::Ptr<RecognitionEngine> r, cv::Ptr<Collection> m, int vcap) :
	_engine {e}, _collector {c}, _tracker {t}, _recengine{r}, _model{m},
	_vcap {cv::VideoCapture(vcap)}
{
	_engine_wait_ms = e->getEngineWait();
}


CoreManager::CoreManager(cv::Ptr<Engine> e, cv::Ptr<Collector> c, cv::Ptr<Tracker> t, cv::Ptr<RecognitionEngine> r, cv::Ptr<Collection> m, cv::VideoCapture vcap) :
	_engine {e}, _collector {c}, _tracker {t}, _recengine{r}, _model{m},
	_vcap {vcap}
{
	_engine_wait_ms = e->getEngineWait();
}

CoreManager::~CoreManager()
{
	//	stopAllThreads();
}

void CoreManager::setFeatureThreshold(int thres)
{
	this->_feature_thres = thres;
}

void CoreManager::setReceiver(cv::Ptr<Receiver> recv)
{
	_receiver = recv;
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

void CoreManager::startMonitoring()
{
	_recengine_stop.store(false);
	std::thread t(&CoreManager::monitor, this);
	t.detach();
}

void CoreManager::startReceiving()
{
	if(_receiver != nullptr)
	{
		std::thread t(&CoreManager::receive, this);
		t.detach();
	}
}

void CoreManager::monitor()
{
	while(!_recengine_stop.load())
	{
		if(_model == nullptr || _model.empty()) continue;
		
		// scan model
		std::vector<int> delIds;	// stores Ids of items to be deleted
		for(P_ImgObj& img : _model->getImgObjects())
		{
			// check if id is NOT in map
			if(_monitor_ids.find(img->getId()) == _monitor_ids.end())
			{
				_monitor_ids.emplace(img->getId());	// new object arrived
				_recengine->recognise(img);
			}
			// check num features - synchronise!
			_tm_lock.lock();
			int numFeatures = img->getNumFeatures();
			_tm_lock.unlock();
			
			if(numFeatures< _feature_thres && img->isTracked() )
			{
				// mark for deletion
				delIds.push_back(img->getId());
				continue;
			}
			// TODO: decide if need to check area of bounding rect
		}
		
		// delete outside ranged-for
		for(int id : delIds)
		{		
			// remove from set and collection
			_monitor_ids.erase(	_monitor_ids.find(id) );
			_model->remove(id);
		}
		
		delIds.clear();
	}	
}

void CoreManager::receive()
{
	while(!_receiver_stop.load())
	{
		P_ImgObj img;
		_receiver->receiveObject(img);
	}
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
		 _tracker_stop.load() && 
		 _recengine_stop.load() &&
		 _receiver_stop.load()))
	{
		_engine_stop.store(true);
		_vcap_stop.store(true);
		_collector_stop.store(true);
		_tracker_stop.store(true);
		_recengine_stop.store(true);
		_receiver_stop.store(true);
		// give engine a chance to stop (sum of preset wait + engine wait)
		std::this_thread::sleep_for(std::chrono::milliseconds(_stop_thread_wait_ms+_engine_wait_ms));
	}
}

} // namespace ce
