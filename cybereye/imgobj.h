#ifndef CE_IMGOBJ_H
#define CE_IMGOBJ_H
#include "opencv2/core.hpp"
#include <atomic>
#include <mutex>

namespace ce {

class ImgObj
{
private:
	cv::Mat						_img;
	int							_id;
	cv::Rect					_boundRect;
	std::vector<cv::Point2f>	_features;
	bool						_tracked = false;
	int							_num_features {0};

public:
    ImgObj(cv::Mat data, int id, cv::Rect rec);
    ImgObj(cv::Mat data, int id);
	ImgObj(int id, cv::Point location);
	
	void setFeatures(std::vector<cv::Point2f> &features);
	
	/**
	 * @brief getFeatures Returns a reference to feature vector of points
	 * @return 
	 */
	std::vector<cv::Point2f> &getFeatures();
	
	void setBoundingRect(cv::Rect rec);
	cv::Rect getBoundingRect();
	
	int getId();
	const cv::Mat& getImgData();
	bool isTracked();
	int	 getNumFeatures();
};

typedef cv::Ptr<ce::ImgObj> P_ImgObj;

} // namespace ce

#endif // CE_IMGOBJ_H
