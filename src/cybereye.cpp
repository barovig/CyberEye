#include "cybereye.h"

namespace ce {

CyberEye::CyberEye()
{
	_model = new Model();
	_manager = new CoreManager(new BkgSegmentationEngine(_model), new Collector(), new Tracker(), 0);
}

CyberEye::~CyberEye()
{
	delete _model;
	delete _manager;
}

} // namespace ce
