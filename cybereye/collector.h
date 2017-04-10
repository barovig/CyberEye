#ifndef CE_COLLECTOR_H
#define CE_COLLECTOR_H
#include "opencv2/core.hpp"
#include "collection.h"

namespace ce {

class Collector
{
private:
	
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
	
	// gets original input frame
    virtual void getFrame(const cv::Mat& input, cv::Mat& output) = 0;
};

} // namespace ce

#endif // CE_COLLECTOR_H
