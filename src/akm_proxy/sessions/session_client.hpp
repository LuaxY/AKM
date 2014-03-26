#ifndef SESSION_CLIENT_HPP
#define SESSION_CLIENT_HPP

#include "akm/network/session.hpp"
#include <deque>

class session_client : public akm::network::session
{
public:
    session_client(boost::asio::ip::tcp::socket _socket) :
        session(std::move(_socket), "CLIENT")
    {
        init();
    }

private:
    void init();
    void handle();
    std::deque<char> m_buffer;
};

#endif // SESSION_CLIENT_HPP