#ifndef CE_OBJECTDISPATCHER_H
#define CE_OBJECTDISPATCHER_H
#include "dispatcher.h"

namespace ce {

class ObjectDispatcher : public ce::Dispatcher
{
public:
	// interface realisation
	void dispatchObject(ce::ImgObj object);
	ObjectDispatcher();
};

} // namespace ce

#endif // CE_OBJECTDISPATCHER_H
