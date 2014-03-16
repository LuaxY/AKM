#ifndef SESSION_CLIENT_INFO_HPP
#define SESSION_CLIENT_INFO_HPP

#include "akm/network/session.hpp"

class session_client_info : public akm::network::session
{
public:
	session_client_info(boost::asio::ip::tcp::socket _socket) :
		session(std::move(_socket), "INFO")
	{}

private:
	void handle();
};

#endif // SESSION_CLIENT_INFO_HPP