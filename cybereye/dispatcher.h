#ifndef CE_DISPATCHER_H
#define CE_DISPATCHER_H
#include "imgobj.h"

namespace ce {

// dispatcher interface
class Dispatcher
{
public:
	virtual void dispatchObject(ce::ImgObj obj) = 0;
};

} // namespace cybeye

#endif // CE_DISPATCHER_H
