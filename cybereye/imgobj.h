#ifndef CE_IMGOBJ_H
#define CE_IMGOBJ_H
#include "opencv2/core.hpp"

namespace ce {

class ImgObj
{
private:
	cv::Mat						_img;
	int							_id;
    cv::Point					_loc;
	cv::Size					_size;
	std::vector<cv::Point2f>	_features;
	
public:
    ImgObj(cv::Mat data, int id, cv::Point2i location, cv::Size size);
    ImgObj(cv::Mat data, int id);
	ImgObj(int id, cv::Point2i location, cv::Size size);
	void setLocation(cv::Point loc);
	void setSize(cv::Size size);
	void setFeatures(std::vector<cv::Point2f> features);
};

} // namespace ce

#endif // CE_IMGOBJ_H
