#include "objreceiver.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
namespace ce {

ObjReceiver::ObjReceiver(int port) : 
	_port{port},
	_acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))
{
}

void ObjReceiver::receiveObject(P_ImgObj obj)
{
	CV_Assert(_engine != nullptr);
	cv::Mat img;
	
	// wait for connection
	boost::asio::ip::tcp::socket socket(_ios);
	_acceptor.accept(socket);
	// get img data
	
	// read actual data
	std::string inbound_data = TcpChannel::readString(socket);
	CV_Assert(inbound_data.size() != 0);
	
	std::istringstream archive_is(inbound_data);
	// deserialise the string - use scope to close stream 
	{
//		boost::archive::text_iarchive arch(archive_is);
		boost::archive::binary_iarchive arch(archive_is);
		
		arch >> img;
	}	

	// construct new ImgObject
	P_ImgObj pImg(new ImgObj(img, 0));	//TODO: deal with ID!
	// run recognition and get text data back
	_engine->recognise(pImg);
	std::string label = _engine->getRecognitionResult();
	
	// send this data back through same socket - header + data
	TcpChannel::writeString(label, socket);
}

void ObjReceiver::setEngine(cv::Ptr<RecognitionEngine> engine)
{
	_engine = engine;	
}

} // namespace ce
