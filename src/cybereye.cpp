#include "cybereye.h"

namespace ce {

CyberEye::CyberEye()
{
	_model = new ce::ObjCollection();
	_engine = new ce::BkgSegmentationEngine(_model, BkgSegmentationEngine::BKG_MOG2);
	_tracker = new ce::ObjTracker();
	_collector = new ce::ImgCollector();
	_manager = new CoreManager(_engine, _collector, _tracker, 0);
}

CyberEye::~CyberEye()
{
}

} // namespace ce
