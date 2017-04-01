#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/core.hpp"

namespace ce {

class Collector
{
public:
	Collector();
    virtual cv::Mat getFrame(cv::Mat frame) = 0;
};

} // namespace ce

#endif // CE_COLLECTOR_H
