#include "cybereye.h"

namespace ce {

CyberEye::CyberEye()
{
	_vcap_index = 0;
}

CyberEye::CyberEye(int vcap)
{
	_vcap_index = 0;
}

CyberEye::~CyberEye()
{
}

void CyberEye::initialise()
{
	_model = cv::Ptr<ObjCollection>(new ObjCollection());
	_engine = cv::Ptr<WatershedEngine>(new WatershedEngine(_model));
	_tracker = cv::Ptr<ObjTracker>(new ObjTracker(_model));
	_collector = cv::Ptr<ImgCollector>(new ImgCollector(_model));
	_recengine = cv::Ptr<RecognitionEngine>(new RecognitionEngine());	
	_manager = cv::Ptr<CoreManager>(new CoreManager(_engine, _collector, _tracker, 
													_recengine, _model, _vcap_index));
}

void CyberEye::start()
{
	_manager->startCapture();
	_manager->startSegmentation();
	_manager->startTracking();
	_manager->startMonitoring();
}

void CyberEye::stop()
{
	_manager->stopAllThreads();
}

void CyberEye::segment(cv::Mat mask)
{
	_engine->setSupervisedInput(mask);
	_manager->triggerSegmentation();
}

void CyberEye::getFrame(cv::Mat& frame)
{
	_manager->getFrame(frame);
}

const std::vector<ImgObj> &CyberEye::getImages()
{
	return _model->getImgObjects();	
}

} // namespace ce
