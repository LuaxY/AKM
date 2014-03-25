#ifndef MASTER_HPP
#define MASTER_HPP

#include <iostream>
#include <memory>

#include "akm/serialization/singleton.hpp"
#include "akm/network/server.hpp"
#include "akm/logger/logger.hpp"

#include "sessions/session_client_info.hpp"
#include "sessions/session_client_sound.hpp"
#include "sessions/session_reg_engine.hpp"

class master : public akm::serialization::singleton<master>
{
public:
    master()
    {
    }

    void start(unsigned short port)
    {
        try
        {
            boost::asio::io_service io_service;

            master_client_info = new akm::network::server<session_client_info>(io_service, port);
            master_client_sound = new akm::network::server<session_client_sound>(io_service, port + 1);
            master_reg_engine = new akm::network::server<session_reg_engine>(io_service, port + 2);

            io_service.run();
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    akm::network::server<session_client_info>* get_master_client_info()
    { return master_client_info; }

    akm::network::server<session_client_sound>* get_master_client_sound()
    { return master_client_sound; }

    akm::network::server<session_reg_engine>* get_master_reg_engine()
    { return master_reg_engine; }

private:
    akm::network::server<session_client_info>* master_client_info;
    akm::network::server<session_client_sound>* master_client_sound;
    akm::network::server<session_reg_engine>* master_reg_engine;
};

#endif // MASTER_HPP