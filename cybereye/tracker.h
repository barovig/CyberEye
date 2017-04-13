#ifndef CE_TRACKER_H
#define CE_TRACKER_H
#include "opencv2/core.hpp"
#include "collection.h"

namespace ce {

class Tracker
{
protected:
	cv::Ptr<ce::Collection> _model;
public:
	Tracker(cv::Ptr<ce::Collection> model);
	virtual void track(const cv::Mat& frame) = 0;
};

} // namespace ce

#endif // CE_TRACKER_H
