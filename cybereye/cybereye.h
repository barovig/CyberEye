#ifndef CE_CYBEREYE_H
#define CE_CYBEREYE_H
#include "coremanager.h"
#include "objcollection.h"
#include "objtracker.h"
#include "imgcollector.h"
#include "bkgsegmentationengine.h"
#include "opencv2/imgproc.hpp"

namespace ce {

class CyberEye
{
private:
	cv::Ptr<ce::CoreManager>			_manager;
	cv::Ptr<ce::BkgSegmentationEngine>	_engine;
	cv::Ptr<ce::ImgCollector>			_collector;
	cv::Ptr<ce::ObjTracker>				_tracker;
	cv::Ptr<ce::ObjCollection>			_model;
	int									_vcap_index;
public:
	CyberEye();
	CyberEye(int vcap);
	~CyberEye();
	void initialise();
	void start();
	void stop();
	// pass frame as ouptut arg
	void getFrame(cv::Mat& frame);
	
	// debugging methods
	cv::Mat getMask();
	const std::vector<ce::ImgObj>& getImages();
};

} // namespace ce

#endif // CE_CYBEREYE_H
