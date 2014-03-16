#ifndef SESSION_CLIENT_LOGIN_HPP
#define SESSION_CLIENT_LOGIN_HPP

#include "akm/network/session.hpp"

namespace akm {
namespace network {

class session_client_login : public session
{
public:
	session_client_login(boost::asio::ip::tcp::socket _socket) :
		session(std::move(_socket), "CLIENT_LOGIN")
	{}

private:
	void handle();
};

} // namespace network
} // namespace akm

#endif // SESSION_CLIENT_LOGIN_HPP