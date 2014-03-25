#include "sessions/session_client.hpp"
#include "sessions/session_server.hpp"
#include "master.hpp"

void session_client::init()
{
    master::instance().connect_to_ankama();
}

void session_client::handle()
{
    std::shared_ptr<session_server> main_session = master::instance().get_master_server()->get_session(0);
    main_session->write(buffer.data(), size);
}