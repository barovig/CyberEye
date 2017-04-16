#include "objectdispatcher.h"

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
	
	boost::asio::io_service			ios;
	boost::system::error_code		err;
	boost::asio::ip::tcp::endpoint  endpt(
									boost::asio::ip::address::from_string(_addr), _port);
	boost::asio::ip::tcp::socket	socket(ios);
	
	socket.connect(endpt);
	
	// create archive and stream
	// NOTE: because binary_oarchive is non-portable, use text_archive
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);	
    archive << _data;
    std::string outbound_data = archive_stream.str();	// string data to send
	
	// create stringstream for header data
	std::ostringstream header_stream;
	// send data size as hex num string, note fixed length
	header_stream << std::setw(HEADER_LENGTH) << std::hex << outbound_data.size();
	
	// sanity check
	if(!header_stream || header_stream.str().size() != HEADER_LENGTH)
	{
		std::cerr << "Sent header length and declared length mismatch!" << std::endl;
		return;
	}
	
	std::string outbound_header = header_stream.str();	// create string for header 
	
	// write all data to socket using vector of buffers
	
	std::vector<boost::asio::const_buffer> buffs;
	buffs.push_back(boost::asio::buffer(outbound_header));
	buffs.push_back(boost::asio::buffer(outbound_data));
	socket.write_some(buffs, err);
	
	// WAIT for label data to come back
	// local buffers and vars
	char inbound_header[HEADER_LENGTH];
	std::vector<char> inbound_data;
	size_t data_sz = 0;	
	
	
	{	// autoclose stream
		socket.read_some(boost::asio::buffer(inbound_header), err);
		std::istringstream is(std::string(inbound_header, HEADER_LENGTH));
		if( !(is >> std::hex >> data_sz) )
		{
			err = boost::asio::error::invalid_argument;
			std::cerr << err.message() << std::endl;
			return;
		}
	}
	
	inbound_data.resize(data_sz);
	// get data from socket
	socket.read_some(boost::asio::buffer(inbound_data), err);
	std::string inbound_label(&inbound_data[0], inbound_data.size());
	
	// set label for _img - CHECK IF STILL VALID!!!!!
	if(_img != nullptr)
		_img->setLabel(inbound_label);
}

ObjectDispatcher::ObjectDispatcher() : Dispatcher()
{
	
}

} // namespace ce
