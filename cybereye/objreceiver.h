#ifndef OBJRECEIVER_H
#define OBJRECEIVER_H
#include "receiver.h"
#include "recognitionengine.h"
#include "objectdispatcher.h"	//for consts and boost headers
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

namespace ce {

class ObjReceiver : public ce::Receiver
{
private:
	cv::Ptr<ce::RecognitionEngine> _engine;
	
	// configs
	int								_port;
	boost::asio::io_service			_ios;	
	boost::asio::ip::tcp::acceptor	_acceptor;
public:
	ObjReceiver(int port);
	// Receiver interface
public:
	void receiveObject(P_ImgObj obj);
	
	void setEngine(cv::Ptr<ce::RecognitionEngine> engine);
};

} // namespace ce

#endif // OBJRECEIVER_H
