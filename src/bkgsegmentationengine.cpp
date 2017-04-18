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

void BkgSegmentationEngine::segment(cv::Mat frame)
{
	static int itr = 0;
	// apply gaussian blur first, with 5x5 kernel
	cv::GaussianBlur(frame, frame, _kernel_sz, _kernel_sigmaX);
	
	// perform background subtraction
	_subtractor->apply(frame, _mask);
	
	if(++itr > NUM_ITERS_FOR_EXTRACT)
	{
		itr = 0;
		// extract individual patches of frame based on mask
		std::vector<cv::Rect> rectangles;
		findConnectedComponents(_mask,rectangles);
		
		// construct ImgObjects and
		for(cv::Rect r : rectangles){
			cv::Ptr<cv::Mat> data(new cv::Mat(frame, r));
			cv::rectangle(_mask,r, cv::Scalar(0xFF,0xFF,0xFF));
			_model->add(data, r);
		}
	}
	
}

void BkgSegmentationEngine::setSupervisedInput(cv::InputArray input)
{
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

// connected components cleanup. (Kaehler & Bradski)
void BkgSegmentationEngine::findConnectedComponents(cv::Mat &mask, std::vector<cv::Rect> &bbs, float perimScale)
{
	// morphological opening/closing to clear up small noise
	cv::morphologyEx(mask, mask, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1,-1), CVCLOSE_ITR);
	cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), CVCLOSE_ITR);
	
	// find contours
	std::vector< std::vector<cv::Point> > contours_all;
	std::vector< std::vector<cv::Point> > contours;
	// RETR_EXTERNAL - retrieve external contours, simple vert/horis approximation
	cv::findContours(mask, contours_all, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	// remove too small contours
	for(auto c : contours_all){
		// find length
		int len = cv::arcLength(c, true);
		
		if(len >= perimScale)
		{
			std::vector<cv::Point> c_new;
			// get convex hull - no specific need for poly
			cv::convexHull(c, c_new);
			contours.push_back(c_new);
		}
		
		// get bounding rects
		
		for(auto c : contours)
		{
			bbs.push_back(boundingRect(c));
		}
	}
}

} // namespace ce
