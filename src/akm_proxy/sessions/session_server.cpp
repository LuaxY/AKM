#include "sessions/session_server.hpp"
#include "sessions/session_client.hpp"
#include "master.hpp"

void session_server::handle()
{
	std::shared_ptr<session_client> main_session = master::instance().get_master_client()->get_session(0);
	main_session->write(buffer.data(), size);
}