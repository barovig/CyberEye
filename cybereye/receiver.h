#ifndef CE_RECEIVER_H
#define CE_RECEIVER_H
#include "imgobj.h"
#include "tcpchannel.h"


namespace ce {

class Receiver
{
public:
	Receiver(){}
	virtual ~Receiver(){}
	virtual void receiveObject(P_ImgObj obj) = 0;
};

} // namespace ce
#endif // CE_RECEIVER_H
