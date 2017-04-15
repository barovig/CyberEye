#ifndef CE_OBJECTDISPATCHER_H
#define CE_OBJECTDISPATCHER_H
#include "dispatcher.h"

namespace ce {

class ObjectDispatcher : public ce::Dispatcher
{
private:
//	boost::asio::io_service			_ios;
//	std::string						_addr = "192.168.1.15";
//	int								_port = 13491;
//	boost::asio::ip::tcp::socket	_socket;
//	boost::system::error_code		_err;
//	const int HEADER_LENGTH = 8;
public:
	// interface realisation
	void dispatchObject(ce::ImgObj object);
	ObjectDispatcher();
};

} // namespace ce

#endif // CE_OBJECTDISPATCHER_H
