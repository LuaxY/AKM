#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>
#include <vector>
#include <stdexcept>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "akm/network/session.hpp"
#include "akm/logger/logger.hpp"

namespace akm {
namespace network {

template<typename T>
class server
{
public:
	server<T>(boost::asio::io_service& io_service, unsigned short port) :
		acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		socket(io_service)
	{
		akm::logger::info() << "server listen port " << port;
		accept();
	}

	std::shared_ptr<T> get_session(int index)
	{
		if (users.size() == 0 || index > users.size() - 1)
			throw std::out_of_range("index is out of range for users");

		return users[index];
	}

private:
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;
	std::vector<std::shared_ptr<T>> users;

	void accept()
	{
		acceptor.async_accept(
			socket,
			boost::bind(
				&server::handle,
				this,
				boost::asio::placeholders::error));
	}

	void handle(boost::system::error_code error)
	{
		if (!error)
		{
			std::shared_ptr<T> client(new T(std::move(socket)));
            users.push_back(client);

            boost::thread th(&T::start, client);
		}
		else
		{
			akm::logger::error() << error << " " << error.message();
		}
		
		accept();
	}
};

} // namespace network
} // namespace akm

#endif // SERVER_HPP