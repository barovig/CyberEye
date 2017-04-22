#ifndef OBJRECEIVER_H
#define OBJRECEIVER_H
#include "receiver.h"
#include "recognitionengine.h"
#include "objectdispatcher.h"	//for consts and boost headers
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

namespace ce {
/**
 * @brief The ObjReceiver class. This class listens for incoming image objects and 
 * runs the configured RecognitionEngine to perform object recognition, before sending 
 * the result back to caller.
 */
class ObjReceiver : public ce::Receiver
{
private:
	cv::Ptr<ce::RecognitionEngine> _engine;
	
	// configs
	int								_port;
	boost::asio::io_service			_ios;	
	boost::asio::ip::tcp::acceptor	_acceptor;
public:
	/**
	 * @brief ObjReceiver only constructor. Ensure port is set.
	 * @param port Integer value for port number
	 */
	ObjReceiver(int port);
	// Receiver interface
public:
	/**
	 * @brief Receiver interface. Receives the incoming object, deserialises and stores it 
	 * in passed pointer
	 * @param obj cv::Ptr of ImgObj where incoming data will be stored.
	 */
	void receiveObject(P_ImgObj obj);
	/**
	 * @brief A setter for RecognitionEngine to use for incoming ImgObj's.
	 * @param engine Smart pointer to RecognitionEngine.
	 */ 
	void setEngine(cv::Ptr<ce::RecognitionEngine> engine);
};

} // namespace ce

#endif // OBJRECEIVER_H
