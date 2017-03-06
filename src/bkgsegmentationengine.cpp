#include "bkgsegmentationengine.h"

namespace ce {

void BkgSegmentationEngine::createSubtractor()
{
    _subtractor = cv::createBackgroundSubtractorMOG2();
}

void BkgSegmentationEngine::updateImgObjects()
{
    // extract individual patches of frame based on mask

    // construct ImgObjects and

    // add to model
}

BkgSegmentationEngine::BkgSegmentationEngine(Model *model) :
    Engine::Engine(model)
{
    createSubtractor();
}

void BkgSegmentationEngine::getImgObjects(cv::Mat frame)
{
    _frame = frame;
    std::thread t(&BkgSegmentationEngine::updateImgObjects, this);
    t.detach();
}

void BkgSegmentationEngine::updateSubtractor(cv::Mat frame)
{
    _subtractor->apply(frame, _mask);
}

} // namespace ce
