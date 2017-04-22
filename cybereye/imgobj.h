#ifndef CE_IMGOBJ_H
#define CE_IMGOBJ_H
#include "opencv2/core.hpp"
#include <atomic>
#include <mutex>

namespace ce {

/**
 * @brief The ImgObj class. This class models an object detected in a frame.
 * It stores the image data in cv::Mat, a collection of tracked features and 
 * text label for the object.
 */
class ImgObj
{
private:
	cv::Mat						_img;
	int							_id;
	cv::Rect					_boundRect;
	std::vector<cv::Point2f>	_features;
	bool						_tracked = false;
	int							_num_features {0};
	std::string					_label;
public:
	/**
	 * @brief ImgObj contrusctor.
	 * @param data cv::Mat with image data.
	 * @param id An integer ID of an object.
	 * @param rec A cv::Rect bounding rectangle specifying object's location
	 * relative to the frame.
	 */
    ImgObj(cv::Mat data, int id, cv::Rect rec);
	/**
	 * @brief ImgObj constructor.
	 * @param data cv::Mat with image data.
	 * @param id An integer ID of an object.
	 */
    ImgObj(cv::Mat data, int id);
	
	/**
	 * @brief A method which sets the collection of features of ImgObj.
	 * @param features an STL vector of detected feature points.
	 */
	void setFeatures(std::vector<cv::Point2f> &features);
	
	/**
	 * @brief A getter for features of an object.
	 * @return A reference to the vector of feature points.
	 */
	std::vector<cv::Point2f> &getFeatures();
	/**
	 * @brief This method sets the bounding rectangle for an object.
	 * @param rec A bounding rectangle.
	 */
	void setBoundingRect(cv::Rect rec);
	/**
	 * @brief This method returns the bounding rectangle of an object.
	 * @return cv::Rect with bounding rectangle.
	 */
	cv::Rect getBoundingRect();
	/**
	 * @brief Getter for an ID.
	 * @return integer ID.
	 */
	int getId();
	/**
	 * @brief A getter for underlying image data of an object.
	 * @return const reference to cv::Mat containing image data.
	 */
	const cv::Mat& getImgData();
	/**
	 * @brief Checks if an object is being tracked with Tracker
	 * @return boolean indicating if object is tracked.
	 */
	bool isTracked();
	/**
	 * @brief A getter for a number of features in collection.
	 * @return An integer number of features.
	 */
	int	 getNumFeatures();
	/**
	 * @brief A setter for label for an ImgObj.
	 * @param label A string to which label will be set.
	 */
	void setLabel(std::string label);
	/**
	 * @brief Getter for text label.
	 * @return String representation of the label.
	 */
	std::string getLabel();
};

typedef cv::Ptr<ce::ImgObj> P_ImgObj;

} // namespace ce

#endif // CE_IMGOBJ_H
