#ifndef CE_OBJTRACKER_H
#define CE_OBJTRACKER_H
#include "tracker.h"
#include "opencv2/video/tracking.hpp"

namespace ce {

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
	int				_num_feature_thres = 3;
	
public:
	ObjTracker(cv::Ptr<ce::Collection> model);
	void track(const cv::Mat& frame);
};

} // namespace ce

#endif // CE_OBJTRACKER_H
