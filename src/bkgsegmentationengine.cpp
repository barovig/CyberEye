#include "bkgsegmentationengine.h"

namespace ce {

void BkgSegmentationEngine::createSubtractor()
{
    _subtractor = cv::createBackgroundSubtractorMOG2();
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

void BkgSegmentationEngine::setUpdateFlag(bool update)
{
	_update = update;
}

//////////// DELETE ME ///////////////
cv::Mat BkgSegmentationEngine::getMask()
{
	cv::Mat mask;
	_mask.copyTo(mask);
	if(!mask.empty())
	{
		cv::erode(mask, mask, cv::Mat(), cv::Point(-1,-1), 4);
		cv::dilate(mask, mask, cv::Mat(), cv::Point(-1,-1), 4);
	}
	return _mask;
}

} // namespace ce
