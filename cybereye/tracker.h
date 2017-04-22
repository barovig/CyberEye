#ifndef CE_TRACKER_H
#define CE_TRACKER_H
#include "opencv2/core.hpp"
#include "collection.h"

namespace ce {

/**
 * @brief The Tracker interface. Contains methods that all trackers must implement.
 */
class Tracker
{
protected:
	cv::Ptr<ce::Collection> _model;
public:
	/**
	 * @brief Tracker constructor.
	 * @param model A smart pointer to Collection of objects.
	 */
	Tracker(cv::Ptr<ce::Collection> model);
	/**
	 * @brief Pure virtual interface method. Tracks the objects from collection 
	 * and updates their location.
	 * @param frame A reference to cv::Mat of a frame where objects will be tracked.
	 */
	virtual void track(const cv::Mat& frame) = 0;
};

} // namespace ce

#endif // CE_TRACKER_H
