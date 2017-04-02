#include "cybereye.h"

namespace ce {

CyberEye::CyberEye()
{
	_vcap_index = 0;
}

CyberEye::CyberEye(int vcap)
{
}

CyberEye::~CyberEye()
{
}

void CyberEye::initialise()
{
	_model = new ce::ObjCollection();
	_engine = new ce::BkgSegmentationEngine(_model, BkgSegmentationEngine::BKG_MOG2);
	_tracker = new ce::ObjTracker();
	_collector = new ce::ImgCollector();
	_manager = new CoreManager(_engine, _collector, _tracker, _vcap_index);
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
