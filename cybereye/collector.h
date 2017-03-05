#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/opencv.hpp"

namespace ce {

class Collector
{
public:
	Collector();
	virtual cv::Mat getCurrentFrame() = 0;
};

} // namespace ce

#endif // CE_COLLECTOR_H
