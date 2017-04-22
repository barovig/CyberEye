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
	/**
	 * @brief _feature_count cv::goodFeaturesToTrack parameter.
	 */
	const int		_feature_count = 500;
	/**
	 * @brief _quality_level cv::goodFeaturesToTrack parameter.
	 */
	const double	_quality_level = 0.01;
	/**
	 * @brief _min_distance cv::goodFeaturesToTrack parameter.
	 */
	const int		_min_distance = 10;
	/**
	 * @brief _lk_max_level cv::calcOpticalFlowPyrLK parameter.
	 */
	const int		_lk_max_level = 3;
	/**
	 * @brief _lk_flags cv::calcOpticalFlowPyrLK parameter.
	 */
	const int		_lk_flags = 0;
	/**
	 * @brief _lk_eig_thres cv::calcOpticalFlowPyrLK parameter.
	 */
	const int		_lk_eig_thres = 0.001;
	/**
	 * @brief _prev_frame Stores previous frame used in optical flow calculation.
	 */
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
