#include "tcpchannel.h"

namespace ce {

TcpChannel::TcpChannel()
{
	
}

void TcpChannel::writeString(std::string data, boost::asio::ip::tcp::socket &socket)
{
	boost::system::error_code		err;	
	// create stringstream for header data
	std::ostringstream header_stream;
	// send data size as hex num string, note fixed length
	header_stream << std::setw(HEADER_LENGTH) << std::hex << data.size();
	
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
	buffs.push_back(boost::asio::buffer(data));
	socket.write_some(buffs, err);	
}

std::string TcpChannel::readString(boost::asio::ip::tcp::socket &socket)
{
	boost::system::error_code	err;
	char						buff_header[HEADER_LENGTH];
	std::vector<char>			buff_data;
	size_t data_sz = 0;	
	
	// read data into header buffer and construct stream
	socket.receive(boost::asio::buffer(buff_header));
	std::istringstream is(std::string(buff_header, HEADER_LENGTH));
	if( !(is >> std::hex >> data_sz) )
	{
		err = boost::asio::error::invalid_argument;
		std::cerr << err.message() << std::endl;
		return 0;
	}
	
	buff_data.resize(data_sz);
	// read actual data
	socket.receive(boost::asio::buffer(buff_data));
	std::string data(&buff_data[0], buff_data.size());
	
	return data;	
}

} // namespace ce
