#ifndef CE_CYBEREYE_H
#define CE_CYBEREYE_H
#include "coremanager.h"
#include "objcollection.h"
#include "objtracker.h"
#include "imgcollector.h"
#include "bkgsegmentationengine.h"

namespace ce {

class CyberEye
{
private:
	cv::Ptr<ce::CoreManager>	_manager;
	cv::Ptr<ce::Engine>			_engine;
	cv::Ptr<ce::Collector>		_collector;
	cv::Ptr<ce::Tracker>		_tracker;
	cv::Ptr<ce::Collection>		_model;
public:
	CyberEye();
	~CyberEye();
};

} // namespace ce

#endif // CE_CYBEREYE_H
