#ifndef BKGSEGMENTATIONENGINE_H
#define BKGSEGMENTATIONENGINE_H
#include "engine.h"
#include <thread>
#include "opencv2/video.hpp"

namespace ce {

class BkgSegmentationEngine : public Engine
{
private:
    cv::Ptr<cv::BackgroundSubtractor>   _subtractor;
    cv::Mat                             _mask;
    bool                                _update = true;

protected:
    void createSubtractor();
    void extractObjects();

public:
    BkgSegmentationEngine(ce::Model* model);
	
    void fillImgObjects(cv::Mat frame);
    void updateSubtractor(cv::Mat frame);
	void setUpdateFlag(bool update);
	
	cv::Mat getMask();
};

} // namespace ce

#endif // BKGSEGMENTATIONENGINE_H
