#ifndef CE_OBJCOLLECTION_H
#define CE_OBJCOLLECTION_H
#include "collection.h"
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <array>

namespace ce {

/**
 * @brief The ObjCollection class. This class is centralised store of ImgObj's.
 * It maintains the list of detected object at each moment of time and provides 
 * methods to update the collection and individual objects.
 */
class ObjCollection : public ce::Collection
{
private:
	std::vector<P_ImgObj>   _images;
	long					_lastId = 1;
	std::mutex				_collection_lock;
public:
	ObjCollection();
	
	// Collection interface
	/**
	 * @brief Collection interface. Adds new ImgObj from raw data.
	 * @param data A cv::Mat with image data.
	 * @param rec A bounding rectangle of an object.
	 */
	void add(cv::Ptr<cv::Mat> data, cv::Rect rec);
	/**
	 * @brief Collection interface. Removes an ImgObj from collection.
	 * @param id An ID of object to be removed.
	 */
	void remove(int id);
	/**
	 * @brief Collection interface. Clears entire collection.
	 */
	void clear();
	/**
	 * @brief Collection interface. Returns an STL vector of pointers to ImgObj's.
	 * @return std::vector of pointers to ImgObj's.
	 */
	std::vector<P_ImgObj> getImgObjects();
	/**
	 * @brief A method to update the location of an ImgObj within a collection.
	 * @param id An ID of an object.
	 * @param location New location of an object as cv::Point.
	 * @param sz New size of the bounding rectangle as cv::Size.
	 */
	void updateLocation(int id, cv::Point location, cv::Size sz);
	/**
	 * @brief A method to update the label of specified object.
	 * @param id An ID of an ImgObj.
	 * @param label A text for updated label.
	 */
	void updateLabel(int id, std::string label);
private:
	bool similar(const cv::Mat& input, const cv::Mat& I2);
	

};

} // namespace ce

#endif // CE_OBJCOLLECTION_H
