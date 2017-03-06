#include "imgobj.h"

namespace ce {

ImgObj::ImgObj()
{
	
}

ImgObj::ImgObj(cv::Mat data, int id, cv::Point2i location)
{
	_img = data;
	_id = id;
    _loc = location;
}

ImgObj::ImgObj(cv::Mat data, int id)
{
    _img = data;
    _id = id;
}

} // namespace ce
