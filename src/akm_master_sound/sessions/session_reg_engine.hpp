#ifndef SESSION_REG_ENGINE_HPP
#define SESSION_REG_ENGINE_HPP

#include "akm/network/session.hpp"

class session_reg_engine : public akm::network::session
{
public:
	session_reg_engine(boost::asio::ip::tcp::socket _socket) :
		session(std::move(_socket), "ENGINE")
	{}

private:
	/*void welcome()
	{
		akm::logger::info() << "new connection (" << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << ")";
	}*/

	void handle();
};

#endif // SESSION_REG_ENGINE_HPP