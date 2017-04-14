#ifndef WATERSHEDENGINE_H
#define WATERSHEDENGINE_H
#include "engine.h"
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace ce {
/**
 * @brief The WatershedEngine class. Uses openCV's watershed() segmentation algorithm to perform supervised image segmentation based on user-set markers
 */
class WatershedEngine : public ce::Engine
{
protected:
	/**
	 * @brief Stores mask with user-defined markers used in watershed segmentation
	 */
	cv::Mat	_supervisedData;
	/**
	 * @brief Max area of bounding rectangle for segmented object. Used to differentiate between foreground and background objects
	 */
	int		_maxArea = 0;
public:
	/**
	 * @brief WatershedEngine constructor
	 * @param model - reference to Collection where current ImgObj's are stored
	 */
	WatershedEngine(cv::Ptr<Collection> model);
	
	// Engine interface
public:
	/**
	 * @brief Interface realisation, performs image segmentation using watershed algorithm.
	 * @pre	_supervisedData must be set
	 * @param frame Input cv::Mat upon which to perform watershed segmentation
	 */
	void segment(cv::Mat frame);
	/**
	 * @brief Interface realisation, sets _supervisedData to the one provided by user
	 * @param input
	 */
	void setSupervisedInput(cv::Mat input);
	/**
	 * @brief Interface realisation, returns 0 because segmentation is performed upon user request, not periodically
	 * @return integer value of 0
	 */
	int	 getEngineWait();
	/**
	 * @brief Sets the maximum area of bounding rectangle around segmented object
	 * @param maxArea integer value for bounding rectangle's area
	 */
	void setMaxObjectArea(int maxArea);
};

} // namespace ce

#endif // WATERSHEDENGINE_H
