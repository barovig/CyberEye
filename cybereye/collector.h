#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/core.hpp"

namespace ce {

class Collector
{
public:
	Collector();
	// gets original input frame
    virtual void getFrame(const cv::Mat& input, cv::Mat& output) = 0;
};

} // namespace ce

#endif // CE_COLLECTOR_H
