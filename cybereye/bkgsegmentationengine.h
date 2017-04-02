#ifndef CE_BKGSEGMENTATIONENGINE_H
#define CE_BKGSEGMENTATIONENGINE_H
#include "engine.h"
#include <thread>
#include "opencv2/video.hpp"

namespace ce {

class BkgSegmentationEngine : public Engine
{
public:
	enum Method {BKG_MOG2, BKG_KNN,};
	
private:
    cv::Ptr<cv::BackgroundSubtractor>   _subtractor;
    cv::Mat                             _mask;
    int								    _update = -1;
	Method								_method = BKG_MOG2;
	int									_engine_wait_ms = 10;
	// gaussian blur default params
	cv::Size							_kernel_sz = cv::Size(5,5);
	int									_kernel_sigmaX = 5;
protected:
    void createSubtractor();
	
public:
    BkgSegmentationEngine(ce::Collection* model);
	BkgSegmentationEngine(ce::Collection* model, Method method);
	// Segments 'frame' and populates _model with ImgObjs
    void fillImgObjects(cv::Mat frame);
	int  getEngineWait();
	// Returns mask for foreground objects
	cv::Mat getMask();	
    void updateSubtractor(cv::Mat frame);
	void setUpdateFlag(int update);
	void setMethod(Method m);
	void setEngineWait(int ms);
	// set parameters for GaussianBlur - convolution kernel and sigmaX
	void setBlurParams(cv::Size sz, int sigmaX);
};

} // namespace ce

#endif // CE_BKGSEGMENTATIONENGINE_H
