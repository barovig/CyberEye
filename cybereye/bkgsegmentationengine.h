#ifndef BKGSEGMENTATIONENGINE_H
#define BKGSEGMENTATIONENGINE_H
#include "engine.h"
#include <thread>
#include "opencv2/video.hpp"

namespace ce {

class BkgSegmentationEngine : public Engine
{
public:
	enum Method {BKG_MOG2, BKG_KNN, BKG_THRESH };

private:
    cv::Ptr<cv::BackgroundSubtractor>   _subtractor;
    cv::Mat                             _mask;
    bool                                _update = true;
	Method								_method = BKG_MOG2;
protected:
    void createSubtractor();

public:
    BkgSegmentationEngine(ce::Model* model);
	
    void fillImgObjects(cv::Mat frame);
    void updateSubtractor(cv::Mat frame);
	void setUpdateFlag(int update);
	void setMethod(Method m);
	cv::Mat getMask();
};

} // namespace ce

#endif // BKGSEGMENTATIONENGINE_H
