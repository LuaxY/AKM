#ifndef CLIENT_HPP
#define CLIENT_HPP

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
class client
{
public:
    client<T>(boost::asio::io_service& io_service, std::string ip, unsigned short port) :
        endpoint(boost::asio::ip::address::from_string(ip), port),
        socket(io_service)
    {
        akm::logger::info() << "connect to " << ip << ":" << port;
        connect();
    }

    std::shared_ptr<T> get_session(int index)
    {
        if (users.size() == 0 || index > users.size() - 1)
            throw std::out_of_range("index is out of range for users");

        return users[index];
    }

private:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    std::vector<std::shared_ptr<T>> users;

    void connect()
    {
        socket.async_connect(
            endpoint,
            boost::bind(
                &client::handle,
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
    }
};

} // namespace network
} // namespace akm

#endif // CLIENT_HPP