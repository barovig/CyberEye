#ifndef TCPCHANNEL_H
#define TCPCHANNEL_H
#include <iostream>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace ce {

class TcpChannel
{
private:
	static const int					HEADER_LENGTH = 8;
public:
	TcpChannel();
	static void writeString(std::string data, 
							boost::asio::ip::tcp::socket &socket);
	static std::string readString(boost::asio::ip::tcp::socket &socket);
};

} // namespace ce

#endif // TCPCHANNEL_H
