#include "bkgsegmentationengine.h"

namespace ce {

void BkgSegmentationEngine::createSubtractor()
{
	switch(_method)
	{
	case BKG_MOG2:
		_subtractor = cv::createBackgroundSubtractorMOG2();
		break;
	case BKG_KNN:
		_subtractor = cv::createBackgroundSubtractorKNN();
		break;
	default:
		_subtractor = cv::createBackgroundSubtractorMOG2();
		break;
	}
}

BkgSegmentationEngine::BkgSegmentationEngine(cv::Ptr<Collection> model) :
    Engine::Engine(model)
{
	createSubtractor();
}

BkgSegmentationEngine::BkgSegmentationEngine(cv::Ptr<Collection> model, BkgSegmentationEngine::Method method) :
	Engine::Engine(model)
{
	_method = method;
	createSubtractor();	
}

void BkgSegmentationEngine::fillImgObjects(cv::Mat frame)
{
	// apply gaussian blur first, with 5x5 kernel
	cv::GaussianBlur(frame, frame, _kernel_sz, _kernel_sigmaX);
	
	// perform background subtraction
	_subtractor->apply(frame, _mask);
	
    // extract individual patches of frame based on mask
	
    // construct ImgObjects and

    // add to model	
	
}

int BkgSegmentationEngine::getEngineWait()
{
	return _engine_wait_ms;
}

void BkgSegmentationEngine::updateSubtractor(cv::Mat frame)
{
	_subtractor->apply(frame, _mask, _update);
}

void BkgSegmentationEngine::setUpdateFlag(int update)
{
	_update = update;
}

cv::Mat BkgSegmentationEngine::getMask()
{
	return _mask;
}

void BkgSegmentationEngine::setMethod(Method m)
{
	_method = m;
	createSubtractor();
}

void BkgSegmentationEngine::setEngineWait(int ms)
{
	_engine_wait_ms = ms;	
}

void BkgSegmentationEngine::setBlurParams(cv::Size sz, int sigmaX)
{
	_kernel_sigmaX = sigmaX;
	_kernel_sz = sz;
}

} // namespace ce
