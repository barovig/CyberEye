#include "bkgsegmentationengine.h"

namespace ce {

void BkgSegmentationEngine::createSubtractor()
{
    _subtractor = cv::createBackgroundSubtractorMOG2(1000, 25, true);
	//_subtractor = cv::createBackgroundSubtractorKNN();
}

void BkgSegmentationEngine::extractObjects()
{

	
}

BkgSegmentationEngine::BkgSegmentationEngine(Model *model) :
    Engine::Engine(model)
{
    createSubtractor();
}

void BkgSegmentationEngine::fillImgObjects(cv::Mat frame)
{
	//// DELETE ME
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

} // namespace ce
