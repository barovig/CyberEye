#ifndef CE_ENGINE_H
#define CE_ENGINE_H
#include "collection.h"
#include "opencv2/core.hpp"

namespace ce {

/**
 * @brief Interface class for segmentation engines. Provides methods that individual Engines must implement so that 
 * CoreManager class can populate internal list of detected image objects.
 */
class Engine
{
protected:
	/**
	 * @brief OpenCV smart pointer to the instance of Collection containing image objects.
	 */
	cv::Ptr<ce::Collection> _model;
	
public:
	/**
	 * @brief Engine constructor
	 * @param Pointer to instance of Collection
	 */
    Engine(cv::Ptr<Collection> model);
	
	/**
	 * @brief ~Engine Virtual destructor
	 */
	virtual			~Engine(){}
	
	/**
	 * @brief Pure virtual interface method, performs image segmentation and populates Collection with
	 * extracted image objects
	 * @param frame - cv::Mat object upon which to perform segmentation
	 */
    virtual void	segment(cv::Mat frame) = 0;
	
	/**
	 * @brief Pure virtual interface method, sets data used in supervised image segmentation
	 * @param input data used in supervised image segmentation.
	 */
	virtual void	setSupervisedInput(cv::InputArray input) = 0;
	/**
	 * @brief Pure virtual interface method, returns engine's wait time between individual segmentations.
	 * @return int millieconds to wait between segmentations.
	 */
	virtual int		getEngineWait() = 0;	// return zero if derived is supervised segmentaton
	
};

} // namespace ce

#endif // CE_ENGINE_H
