#ifndef CYBEREYE_H
#define CYBEREYE_H
#include "coremanager.h"
#include "bkgsegmentationengine.h"

namespace ce {

class CyberEye
{
private:
	CoreManager* _manager;
	Model*		 _model;
public:
	CyberEye();
	~CyberEye();
};

} // namespace ce

#endif // CYBEREYE_H
