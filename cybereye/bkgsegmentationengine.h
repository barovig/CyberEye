#ifndef CE_BKGSEGMENTATIONENGINE_H
#define CE_BKGSEGMENTATIONENGINE_H
#include "engine.h"
#include <thread>
#include "opencv2/video.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"

namespace ce {

class BkgSegmentationEngine : public Engine
{
public:
	enum Method {BKG_MOG2, BKG_KNN,};
	
private:
	// Constants
	const float DP_EPSILON_DENOMINATOR = 20.0;
	const int	CVCLOSE_ITR = 1;
	const int	NUM_ITERS_FOR_EXTRACT = 100;	// extract ImgObj-s every 1 sec
	// Memebers
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
    BkgSegmentationEngine(cv::Ptr<Collection> model);
	BkgSegmentationEngine(cv::Ptr<Collection> model, Method method);
	
	// Base class overrides
	// Segments 'frame' and populates _model with ImgObjs
    void segment(cv::Mat frame);
	void setSupervisedInput(cv::InputArray input);
	
	int  getEngineWait();
	
	// Returns mask for foreground objects
	cv::Mat getMask();	
	
    void updateSubtractor(cv::Mat frame);
	void setUpdateFlag(int update);
	void setMethod(Method m);
	void setEngineWait(int ms);
	
	// set parameters for GaussianBlur - convolution kernel and sigmaX
	void setBlurParams(cv::Size sz, int sigmaX);
	
private:
	void findConnectedComponents(
				cv::Mat&				mask,
				std::vector<cv::Rect>&	bbs,
				float					perimScale = 400
			);
	
};

} // namespace ce

#endif // CE_BKGSEGMENTATIONENGINE_H
