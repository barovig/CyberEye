#ifndef CE_IMGOBJ_H
#define CE_IMGOBJ_H
#include "opencv2/opencv.hpp"

namespace ce {

class ImgObj
{
private:
	cv::Mat		_img;
	int			_id;
    cv::Point2i	_loc;
public:
	ImgObj();
    ImgObj(cv::Mat data, int id, cv::Point2i location);
};

} // namespace ce

#endif // CE_IMGOBJ_H
