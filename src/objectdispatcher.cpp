#include "objectdispatcher.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace ce {

void ObjectDispatcher::dispatchObject(P_ImgObj object)
{
	// init local data
	object->getImgData().copyTo(_data);
	_img = object;
	// start thread to send data	
	std::thread t(&ObjectDispatcher::dispatch, this);
	t.detach();
}

void ObjectDispatcher::dispatch()
{
	// no data to send
	if(_data.empty()) return;
	
	// construct and open tcp socket
	boost::asio::io_service			ios;
	boost::asio::ip::tcp::endpoint  endpt(
									boost::asio::ip::address::from_string(_addr), _port);
	boost::asio::ip::tcp::socket	socket(ios);
	
	try{
		socket.connect(endpt);
		
		// create archive and stream
		std::ostringstream archive_stream;
		boost::archive::text_oarchive archive(archive_stream);	
//		boost::archive::binary_oarchive archive(archive_stream);
		archive << _data;
		std::string outbound_data = archive_stream.str();	// string data to send
		
		// send data over channel
		TcpChannel::writeString(outbound_data, socket);
		
		// WAIT for label data to come back
		std::string inbound_label = TcpChannel::readString(socket);
		
		// dispatcher initiated connection -> close the socket now
		socket.close();
		
		// set label for _img - CHECK IF PTR IS STILL VALID!!
		if(_img != nullptr)
			_img->setLabel(inbound_label);
	}
	catch(...){
		std::cerr << "Error happened" << std::endl;
	}
}

ObjectDispatcher::ObjectDispatcher(std::string address, int port) : Dispatcher(),
	_addr {address}, _port{port}
{
	
}

} // namespace ce
