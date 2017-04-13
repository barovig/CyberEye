#include "imgobj.h"

namespace ce {

ImgObj::ImgObj(cv::Mat data, int id, cv::Rect rec) :
	_img{data}, _id{id}, _boundRect{rec}
	
{
	
}

ImgObj::ImgObj(cv::Mat data, int id) : 
	_img{data}, _id{id}
{
}

void ImgObj::setFeatures(std::vector<cv::Point2f> &features)
{
	_features.clear();
	for(auto p : features)
		_features.push_back(p);
}

std::vector<cv::Point2f> &ImgObj::getFeatures()
{
	return _features;
}

void ImgObj::setBoundingRect(cv::Rect rec)
{
	_boundRect = rec;
}

cv::Rect ImgObj::getBoundingRect()
{
	return _boundRect;
}

int ImgObj::getId()
{
	return _id;
}

const cv::Mat &ImgObj::getImgData()
{
	return _img;
}



} // namespace ce
