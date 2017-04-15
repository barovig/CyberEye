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
	
	// set label for _img - CHECK IF STILL VALID!!!!!
	
}

ObjectDispatcher::ObjectDispatcher() : Dispatcher()
{
	
}

} // namespace ce
