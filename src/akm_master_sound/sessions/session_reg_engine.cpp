#include "sessions/session_reg_engine.hpp"
#include "sessions/session_client_sound.hpp"
#include "master.hpp"

void session_reg_engine::handle()
{
	std::shared_ptr<session_client_sound> main_session = master::instance().get_master_client_sound()->get_session(0);
	main_session->write(buffer.data(), size);
}