#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <string>
#include <cstring>
#include <sstream>

#include "akm/network/client.hpp"
#include "akm/network/server.hpp"
#include "akm/logger/logger.hpp"

namespace akm {
namespace network {

class session
{
public:
	virtual void start()
	{
        try
        {
            welcome();

            while (socket.is_open())
            {
                boost::system::error_code error;

                size = socket.read_some(boost::asio::buffer(buffer), error);

                if (error == boost::asio::error::eof || size == 0)
                    close();
                else
                {
                    akm::logger::debug() << get_tag() << "data receive, " << size << " bytes";
                    handle();
                }
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
	}

	virtual void write(char* data, int len)
	{
		socket.send(boost::asio::buffer(data, len));
	}

protected:
	session(boost::asio::ip::tcp::socket _socket, std::string _tag) :
		socket(std::move(_socket)),
		tag(_tag)
	{
	}

	boost::asio::ip::tcp::socket socket;
	boost::array<char, 256> buffer;
	int size;
	std::string tag;

	virtual void welcome()
	{
		akm::logger::info() << get_tag() << "new connection (" << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << ")";
	}

	virtual void close()
	{
		akm::logger::info() << get_tag() << "close connection (" << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << ")";
		socket.close();
	}

	virtual void handle() = 0;

	std::string get_tag()
	{
		std::ostringstream tag_format;
		tag_format << "[" << tag << "] ";
		return tag_format.str();
	}
};

} // namespace network
} // namespace akm

#endif // SESSION_HPP