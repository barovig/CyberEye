#ifndef CE_DISPATCHER_H
#define CE_DISPATCHER_H
#include "imgobj.h"
#include "tcpchannel.h"
#include "opencv2/core.hpp"
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::cv::Mat)

namespace ce {

// dispatcher interface
/**
 * @brief The Dispatcher interface. Defines the contract that all Dispatcher's need to realise.
 */
class Dispatcher
{
private:
	
public:
	/**
	 * @brief Dispatcher constructor.
	 */
	Dispatcher(){}
	/**
	 * @brief ~Dispatcher Virtual destructor.
	 */
	virtual ~Dispatcher(){}
	/**
	 * @brief Pure virtual interface method. Dispatcher the ImgObj to the server.
	 * @param obj Smart pointer to ImgObj to be sent.
	 */
	virtual void dispatchObject(P_ImgObj obj) = 0;
};


} // namespace cybeye

#endif // CE_DISPATCHER_H
