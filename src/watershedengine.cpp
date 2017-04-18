#include "watershedengine.h"

namespace ce {

WatershedEngine::WatershedEngine(cv::Ptr<Collection> model) : Engine(model)
{
	
}



void WatershedEngine::WatershedEngine::segment(cv::Mat frame)
{
	CV_Assert(_supervisedData.type() == CV_8UC1);
	
	int compCount = 0;	
	std::vector< std::vector<cv::Point2i> > contours;
	std::vector< cv::Vec4i> hierarchy;
	
	// make sure supervised data is set
	if(_supervisedData.empty())
		return;
	// find contours in mask using 2-level retrieval mode and simple approximation method
	cv::findContours(_supervisedData, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	
	// make sure we found contours
	if(contours.empty()) return;
	
	// create watershed markers mask same size and input data
	cv::Mat markers(_supervisedData.size(), CV_32S);
	markers = cv::Scalar::all(0);
	
	// draw contours from hierarchy into markers mask
	int contourIdx = 0; // index of contour in top level of hierarchy. -1 denotes the last contour
	for( ; contourIdx>= 0; contourIdx = hierarchy[contourIdx][0], compCount++)
		cv::drawContours(markers, contours, contourIdx, cv::Scalar::all(compCount+1), -1, 8, hierarchy, INT_MAX);
	
	// make sure we drew components
	if(compCount == 0) return;
	
	// vector of ROIs
	std::vector< cv::Rect > rectangles;
	
	cv::watershed(frame,markers);
	
	// for each segmented image found
	for(int i = 0; i < compCount; ++i)
	{
		// construct Mat same size and type as markers
		cv::Mat mask(markers.size(), CV_32S);
		
		// construct range mask
		cv::Mat range(markers.size(), CV_32S);
		range = cv::Scalar::all(i+1);
		
		// populate the mask using range mask
		cv::inRange(markers, range, range, mask);
		
		// get bounding rectangle and add to vector
		// TODO: increase rectangle a bit
		cv::Rect rec = cv::boundingRect(mask);
		if(rec.area() < _maxArea)		// if rectangle is same size as frame -> this is background
		{	
			// expand rectangle by 20% if size is not too large
			int height = rec.height * 1.02;
			if(height < frame.rows) rec.height = height;
			
			int width = rec.width * 1.02;
			if(width < frame.cols) rec.width = width;
			
			// shift center, only if we won't go out of frame bounds
//			int x = rec.x - width / 2;
//			if( x > 0) rec.x = x;
			
//			int y = rec.y - height / 2;
//			if( y > 0) rec.y = y;
			
			rectangles.push_back(rec);
		}
	}
	
	for(cv::Rect r : rectangles)
	{
		// extract region of interest
		cv::Mat img(frame,r);
		_model->add(img, r);	
	}
}

void WatershedEngine::WatershedEngine::setSupervisedInput(cv::Mat input)
{
	// create a deep copy
	input.copyTo(_supervisedData);
	// set max area if not set
	if(!_maxArea)
		_maxArea = _supervisedData.size().area();
}

int WatershedEngine::WatershedEngine::getEngineWait()
{
	// no wait for supervised algo
	return 0;
}

void WatershedEngine::setMaxObjectArea(int maxArea)
{
	_maxArea = maxArea;
}

} // namespace ce

