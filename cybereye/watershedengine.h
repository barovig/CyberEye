#ifndef WATERSHEDENGINE_H
#define WATERSHEDENGINE_H
#include "engine.h"

namespace ce {

class WatershedEngine : public ce::Engine
{
public:
	WatershedEngine(cv::Ptr<Collection> model);
	
	
	// Engine interface
public:
	void segment(cv::Mat frame);
	void supervisedSegment(cv::Mat frame, cv::InputArray input);
	int	 getEngineWait();
};

} // namespace ce

#endif // WATERSHEDENGINE_H
