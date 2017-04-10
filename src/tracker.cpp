#include "tracker.h"

namespace ce {

Tracker::Tracker(cv::Ptr<ce::Collection> model)
{
	_model = model;
}

} // namespace ce
