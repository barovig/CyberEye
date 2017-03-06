#include "bkgsegmentationengine.h"

namespace ce {

void BkgSegmentationEngine::createSubtractor()
{
    _subtractor = cv::createBackgroundSubtractorMOG2();
}

BkgSegmentationEngine::BkgSegmentationEngine(Model *model) :
    Engine::Engine(model)
{
    createSubtractor();
}

void BkgSegmentationEngine::getImgObjects(cv::Mat frame)
{
    _frame = frame;
}

void BkgSegmentationEngine::updateSubtractor(cv::Mat frame)
{

}

} // namespace ce
