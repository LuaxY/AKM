#ifndef SESSION_CLIENT_SOUND_HPP
#define SESSION_CLIENT_SOUND_HPP

#include "akm/network/session.hpp"

class session_client_sound : public akm::network::session
{
public:
    session_client_sound(boost::asio::ip::tcp::socket _socket) :
        session(std::move(_socket), "SOUND")
    {}

private:
    void handle();
};
#endif // SESSION_CLIENT_SOUND_HPP