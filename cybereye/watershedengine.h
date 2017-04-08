#ifndef WATERSHEDENGINE_H
#define WATERSHEDENGINE_H
#include "engine.h"
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace ce {
/**
 * @brief The WatershedEngine class. Uses openCV's watershed() segmentation algorithm to perform supervised image segmentation
 */
class WatershedEngine : public ce::Engine
{
protected:
	/**
	 * @brief Stores mask with user-defined markers used in watershed segmentation
	 */
	cv::Mat	_supervisedData;
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
	void setSupervisedInput(cv::InputArray input);
	/**
	 * @brief Interface realisation, returns 0 because segmentation is performed upon user request, not periodically
	 * @return integer value of 0
	 */
	int	 getEngineWait();
};

} // namespace ce

#endif // WATERSHEDENGINE_H
