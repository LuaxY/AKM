#include "sessions/session_client_sound.hpp"
#include "sessions/session_reg_engine.hpp"
#include "master.hpp"

void session_client_sound::handle()
{
	std::shared_ptr<session_reg_engine> main_session = master::instance().get_master_reg_engine()->get_session(0);
	main_session->write(buffer.data(), size);
}