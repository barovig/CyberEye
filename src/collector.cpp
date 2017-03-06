#include "collector.h"

namespace ce {

Collector::Collector()
{

}

Collector::~Collector()
{

}

cv::Mat Collector::getCurrentFrame(cv::Mat frame)
{
    return frame;
}

} // namespace ce
