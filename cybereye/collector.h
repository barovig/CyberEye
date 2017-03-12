#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/core.hpp"

namespace ce {

class Collector
{
public:
	Collector();
    virtual ~Collector();
    cv::Mat getCurrentFrame(cv::Mat frame);
};

} // namespace ce

#endif // CE_COLLECTOR_H
