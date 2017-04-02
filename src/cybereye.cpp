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
	_model = cv::Ptr<ce::ObjCollection>(new ObjCollection());
	_engine = cv::Ptr<ce::BkgSegmentationEngine>(new ce::BkgSegmentationEngine(_model, BkgSegmentationEngine::BKG_MOG2));
	_tracker = cv::Ptr<ObjTracker>(new ce::ObjTracker());
	_collector = cv::Ptr<ImgCollector>(new ce::ImgCollector());
	//_manager = cv::Ptr<CoreManager>(new CoreManager(_engine, _collector, _tracker, _vcap_index));
}

void CyberEye::start()
{
	_manager->startCapture();
	_manager->startSegmentation();
	_manager->startTracking();
}

void CyberEye::stop()
{
	_manager->stopAllThreads();
}

void CyberEye::getFrame(cv::Mat& frame)
{
	_manager->getFrame(frame);
}

cv::Mat CyberEye::getMask()
{
	return _engine->getMask();
}

} // namespace ce
