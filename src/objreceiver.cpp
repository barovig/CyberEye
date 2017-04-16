#include "objreceiver.h"

namespace ce {

ObjReceiver::ObjReceiver() : 
	_acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))
{
}

void ObjReceiver::receiveObject(P_ImgObj obj)
{
	CV_Assert(_engine != nullptr);
	cv::Mat img;
	
	using namespace boost::asio::ip;	
	// get img data
	tcp::socket socket(_ios);
	_acceptor.accept(socket);
	boost::system::error_code err;
	size_t data_sz = 0;
	//  scope will close stream automatically 
	{
		socket.read_some(boost::asio::buffer(_buff_header), err);
		std::istringstream is(std::string(_buff_header, ObjectDispatcher::HEADER_LENGTH));
		if( !(is >> std::hex >> data_sz) )
		{
			err = boost::asio::error::invalid_argument;
			std::cerr << err.message() << std::endl;
			return;
		}		
	}
	_buff_data.resize(data_sz);
	// read actual data
	{
		socket.read_some(boost::asio::buffer(_buff_data), err);
		std::string archive_data(&_buff_data[0], _buff_data.size());
		std::istringstream archive_is(archive_data);
		boost::archive::text_iarchive arch(archive_is);
		
		arch >> img;
	}	
	
	// construct new ImgObject
	P_ImgObj pImg(new ImgObj(img, 0));	//TODO: deal with ID!
	// run recognition and get text data back
	_engine->recognise(pImg);
	std::string label = _engine->getRecognitionResult();
	
	// send this data back though same socket - header + data
}

void ObjReceiver::setEngine(cv::Ptr<RecognitionEngine> engine)
{
	_engine = engine;	
}

} // namespace ce
