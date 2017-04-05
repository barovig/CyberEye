#include "imgobj.h"

namespace ce {

ImgObj::ImgObj(cv::Mat data, int id, cv::Point location, cv::Size size) :
	_img{data}, _id{id}, _loc{location}, _size{size}
{
}


ImgObj::ImgObj(cv::Mat data, int id) : 
	_img{data}, _id{id}
{
}

ImgObj::ImgObj(int id, cv::Point location, cv::Size size) : 
	_id{id}, _loc{location}, _size{size}
{
}

void ImgObj::setLocation(cv::Point loc)
{
	_loc = loc;
}

void ImgObj::setSize(cv::Size size)
{
	_size = size;
}

void ImgObj::setFeatures(std::vector<cv::Point> features)
{
	_features = features;
}

const cv::Mat &ImgObj::getImgData()
{
	return _img;
}



} // namespace ce
