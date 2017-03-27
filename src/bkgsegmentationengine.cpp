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
	case BKG_THRESH:
		_subtractor = new BackgroundSubtractorTH();
		break;
	default:
		_subtractor = cv::createBackgroundSubtractorMOG2();
		break;
	}
}

BkgSegmentationEngine::BkgSegmentationEngine(Model *model) :
    Engine::Engine(model)
{
    createSubtractor();
}

void BkgSegmentationEngine::fillImgObjects(cv::Mat frame)
{
	//// DELETE ME
	if(!frame.empty())
		_subtractor->apply(frame, _mask, _update);
	/// //////////////
    // extract individual patches of frame based on mask
	
    // construct ImgObjects and

    // add to model	
	
}

void BkgSegmentationEngine::updateSubtractor(cv::Mat frame)
{
	_subtractor->apply(frame, _mask, _update);
}

void BkgSegmentationEngine::setUpdateFlag(int update)
{
	_update = update;
}

//////////// DELETE ME ///////////////
cv::Mat BkgSegmentationEngine::getMask()
{
	return _mask;
}

void BkgSegmentationEngine::setMethod(Method m)
{
	_method = m;
	createSubtractor();
}

} // namespace ce
