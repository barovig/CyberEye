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

/**
 * @brief The TcpChannel class. A utility class used in ObjDispatcher 
 * and ObjReceiver to send/read data to/from socket.
 */
class TcpChannel
{
private:
	static const int					HEADER_LENGTH = 8;
public:
	/**
	 * @brief TcpChannel default constructor.
	 */
	TcpChannel();
	/**
	 * @brief Sends text string to boost::asio socket.
	 * @param data String with data to be sent.
	 * @param socket A socket through which data will be sent.
	 */
	static void writeString(std::string data, 
							boost::asio::ip::tcp::socket &socket);
	/**
	 * @brief Reads data from specified boost::asio socket.
	 * @param socket A socket from which data is to be acquired.
	 * @return A string containing received data.
	 */
	static std::string readString(boost::asio::ip::tcp::socket &socket);
};

} // namespace ce

#endif // TCPCHANNEL_H
