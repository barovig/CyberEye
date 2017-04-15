#ifndef CE_OBJCOLLECTION_H
#define CE_OBJCOLLECTION_H
#include "collection.h"
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <array>

namespace ce {

class ObjCollection : public ce::Collection
{
private:
	std::vector<ce::ImgObj> _images;
	long					_lastId = 1;
	
public:
	ObjCollection();
	// Collection interface
	void add(cv::Mat& data, cv::Rect rec);
	void remove(int id);
	std::vector<ce::ImgObj> &getImgObjects();
	void updateLocation(int id, cv::Point location, cv::Size sz);
	void updateLabel(int id, std::string label);
private:
	bool similar(const cv::Mat& input, const cv::Mat& I2);
};

} // namespace ce

#endif // CE_OBJCOLLECTION_H
