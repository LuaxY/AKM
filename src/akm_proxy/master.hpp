#ifndef MASTER_HPP
#define MASTER_HPP

#include <iostream>
#include <memory>

#include "akm/serialization/singleton.hpp"
#include "akm/network/client.hpp"
#include "akm/network/server.hpp"
#include "akm/logger/logger.hpp"

#include "sessions/session_client.hpp"
#include "sessions/session_server.hpp"

class master : public akm::serialization::singleton<master>
{
public:
    master(std::string ip, unsigned short game_port) :
        m_ip(ip),
        m_game_port(game_port)
    {
    }

    void start(unsigned short proxy_port)
    {

        try
        {
            master_client = new akm::network::server<session_client>(io_service, proxy_port);
            
            io_service.run();
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void connect_to_ankama()
    {
        master_server = new akm::network::client<session_server>(io_service, m_ip, m_game_port);
    }

    akm::network::server<session_client>* get_master_client()
    { return master_client; }

    akm::network::client<session_server>* get_master_server()
    { return master_server; }

private:
    akm::network::server<session_client>* master_client;
    akm::network::client<session_server>* master_server;
    boost::asio::io_service io_service;
    std::string     m_ip;
    unsigned short  m_game_port;
};

#endif // MASTER_HPP