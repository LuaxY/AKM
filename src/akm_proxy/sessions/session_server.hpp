#ifndef SESSION_SERVER_HPP
#define SESSION_SERVER_HPP

#include "akm/network/session.hpp"
#include <deque>

class session_server : public akm::network::session
{
public:
    session_server(boost::asio::ip::tcp::socket _socket) :
        session(std::move(_socket), "SERVER")
    {}

private:
    void handle();
    std::deque<char> m_buffer;
};
#endif // SESSION_SERVER_HPP