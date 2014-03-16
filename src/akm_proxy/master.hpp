#ifndef MASTER_HPP
#define MASTER_HPP

#include <iostream>
#include <memory>

#include "akm/serialization/singleton.hpp"
#include "akm/network/server.hpp"
#include "akm/logger/logger.hpp"

#include "akm/network/session_client_login.hpp"

namespace akm {

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

			master_client_login = new akm::network::server<akm::network::session_client_login>(io_service, port);

			io_service.run();
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	akm::network::server<akm::network::session_client_login>* get_master_client_login()
	{ return master_client_login; }

private:
	akm::network::server<akm::network::session_client_login>* master_client_login;
};

} // namespace akm

#endif // MASTER_HPP