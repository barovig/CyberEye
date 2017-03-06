#ifndef BKGSEGMENTATIONENGINE_H
#define BKGSEGMENTATIONENGINE_H
#include "engine.h"
#include <thread>

namespace ce {

class BkgSegmentationEngine : public Engine
{
private:
    cv::Ptr<cv::BackgroundSubtractor>   _subtractor;
    cv::Mat                             _mask;
    bool                                _update = true;
    cv::Mat                             _frame;

protected:
    void createSubtractor();
    void updateImgObjects();

public:
    BkgSegmentationEngine(ce::Model *model);
    void getImgObjects(cv::Mat frame);
    void updateSubtractor(cv::Mat frame);
};

} // namespace ce

#endif // BKGSEGMENTATIONENGINE_H
