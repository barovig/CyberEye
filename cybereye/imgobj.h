#ifndef CE_IMGOBJ_H
#define CE_IMGOBJ_H
#include "opencv2/core.hpp"

namespace ce {

class ImgObj
{
private:
	cv::Mat						_img;
	int							_id;
	cv::Rect					_boundRect;
	std::vector<cv::Point>		_features;
	
public:
    ImgObj(cv::Mat data, int id, cv::Rect rec);
    ImgObj(cv::Mat data, int id);
	ImgObj(int id, cv::Point location);
	
	void setFeatures(std::vector<cv::Point> features);
	std::vector<cv::Point> getFeatures();
	
	void setBoundingRect(cv::Rect rec);
	cv::Rect getBoundingRect();
	
	int getId();
	const cv::Mat& getImgData();

};

} // namespace ce

#endif // CE_IMGOBJ_H
