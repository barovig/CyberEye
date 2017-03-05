#include "coremanager.h"
#include "opencv/cv.h"

namespace ce {

CoreManager::CoreManager(Engine& engine, Collector& collector, Tracker& tracker)
{
	_engine = &engine;
	_collector = &collector;
	_tracker = &tracker;
}

cv::Mat CoreManager::getFrame()
{
	return _collector->getCurrentFrame();
}

} // namespace ce
