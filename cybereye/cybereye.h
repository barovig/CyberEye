#ifndef CE_CYBEREYE_H
#define CE_CYBEREYE_H
#include "coremanager.h"
#include "bkgsegmentationengine.h"

namespace ce {

class CyberEye
{
private:
	cv::Ptr<CoreManager> _manager;
	cv::Ptr<Collection>	 _model;
public:
	CyberEye();
	~CyberEye();
};

} // namespace ce

#endif // CE_CYBEREYE_H
