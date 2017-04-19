#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/core.hpp"
#include "collection.h"

namespace ce {

/**
 * @brief The Collector class. An interface for image collector class used to output detected object data.
 */
class Collector
{	
protected:
	/**
	 * @brief OpenCV smart pointer to the instance of Collection containing image objects.
	 */
	cv::Ptr<ce::Collection> _model;
public:
	/**
	 * @brief Collector constructor
	 * @param model reference to Ptr to Collection
	 */
	Collector(cv::Ptr<ce::Collection> model);
	/**
	 * @brief Pure virtual method used to print image object data to screen.
	 */
    virtual void getFrame(const cv::Mat&, cv::Mat&) = 0;
};

} // namespace ce

#endif // CE_COLLECTOR_H
