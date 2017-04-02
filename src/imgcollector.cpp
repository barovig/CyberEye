#include "imgcollector.h"

namespace ce {

ImgCollector::ImgCollector()
{
	
}

} // namespace ce


void ce::ImgCollector::getFrame(const cv::Mat& input, cv::Mat& output)
{
	input.copyTo(output);
}
