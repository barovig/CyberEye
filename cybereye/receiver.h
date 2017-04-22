#ifndef CE_RECEIVER_H
#define CE_RECEIVER_H
#include "imgobj.h"
#include "tcpchannel.h"


namespace ce {

/**
 * @brief The Receiver interface.
 */
class Receiver
{
public:
	/**
	 * @brief Receiver constructor.
	 */
	Receiver(){}
	virtual ~Receiver(){}
	/**
	 * @brief Pure virtual interface method, receives incoming objects and stores in passed pointer.
	 * @param obj Smart pointer where incoming object will be stored.
	 */
	virtual void receiveObject(P_ImgObj obj) = 0;
};

} // namespace ce
#endif // CE_RECEIVER_H
