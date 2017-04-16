#ifndef CE_RECEIVER_H
#define CE_RECEIVER_H
#include "imgobj.h"

namespace ce {

class Receiver
{
public:
	virtual void receiveObject(P_ImgObj obj) = 0;
};

} // namespace ce
#endif // CE_RECEIVER_H
