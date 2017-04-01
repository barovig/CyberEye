#ifndef CE_IMGCOLLECTOR_H
#define CE_IMGCOLLECTOR_H
#include "collector.h"

namespace ce {

class ImgCollector : public ce::Collector
{
public:
	ImgCollector();
	
	// Collector interface
public:
	cv::Mat getFrame(cv::Mat frame);
};

} // namespace ce

#endif // CE_IMGCOLLECTOR_H
