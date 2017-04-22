#ifndef CE_OBJTRACKER_H
#define CE_OBJTRACKER_H
#include "tracker.h"
#include "opencv2/video/tracking.hpp"

namespace ce {

/**
 * @brief The ObjTracker class. This class encapsulates functionality used in tracking objects
 * in ObjCollection between individual frames.
 */
class ObjTracker : public ce::Tracker
{
protected:
	const int		_feature_count = 500;
	const double	_quality_level = 0.01;
	const int		_min_distance = 10;
	const int		_lk_max_level = 3;
	const int		_lk_flags = 0;
	const int		_lk_eig_thres = 0.001;
	cv::Mat			_prev_frame;
	
public:
	/**
	 * @brief ObjTracker constructor.
	 * @param model A smart pointer to collection.
	 */
	ObjTracker(cv::Ptr<ce::Collection> model);
	/**
	 * @brief Tracker interface. Tracks location changes of objects in ObjCollection.
	 * @param frame A most recent frame where obejcts need to be tracked.
	 */
	void track(const cv::Mat& frame);
};

} // namespace ce

#endif // CE_OBJTRACKER_H
