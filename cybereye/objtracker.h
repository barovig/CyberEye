#ifndef CE_OBJTRACKER_H
#define CE_OBJTRACKER_H
#include "tracker.h"

namespace ce {

class ObjTracker : public ce::Tracker
{
public:
	ObjTracker(cv::Ptr<ce::Collection> model);
};

} // namespace ce

#endif // CE_OBJTRACKER_H
