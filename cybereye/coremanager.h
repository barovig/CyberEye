#ifndef CE_COREMANAGER_H
#define CE_COREMANAGER_H

#include "engine.h"
#include "tracker.h"
#include "collector.h"

namespace ce {

class CoreManager
{
private:
	Engine* _engine;
	Collector* _collector;
	Tracker* _tracker;
public:
	CoreManager(Engine& engine, Collector& collector, Tracker& tracker);
	cv::Mat getFrame();
};


} // namespace ce
#endif // CE_COREMANAGER_H
