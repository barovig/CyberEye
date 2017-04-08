#include "watershedengine.h"

namespace ce {

WatershedEngine::WatershedEngine(cv::Ptr<Collection> model) : Engine(model)
{
	
}

} // namespace ce


void ce::WatershedEngine::segment(cv::Mat frame)
{
}

void ce::WatershedEngine::supervisedSegment(cv::Mat frame, cv::InputArray input)
{
}

int ce::WatershedEngine::getEngineWait()
{
}
