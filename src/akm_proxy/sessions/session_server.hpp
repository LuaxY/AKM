#ifndef SESSION_SERVER_HPP
#define SESSION_SERVER_HPP

#include "akm/network/session.hpp"

class session_server : public akm::network::session
{
public:
	session_server(boost::asio::ip::tcp::socket _socket) :
		session(std::move(_socket), "SERVER")
	{}

private:
	void handle();
};
#endif // SESSION_SERVER_HPP