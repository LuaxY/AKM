#include "sessions/session_client_info.hpp"

void session_client_info::handle()
{
    //std::cout.write(buffer.data(), size);

    if (buffer[0] == '{')
    {
        char answer[] = "{ \"_msg_id\" : \"COMPONENTS_LIST\", \"components\" : [ { \"activated\" : true, \"name\" : \"all\", \"optional\" : true }, { \"activated\" : true, \"name\" : \"base\", \"optional\" : false }, { \"activated\" : true, \"name\" : \"fr\", \"optional\" : true }, { \"activated\" : true, \"name\" : \"subscribed\", \"optional\" : true }, { \"activated\" : true, \"name\" : \"admin\", \"optional\" : true }, { \"activated\" : true, \"name\" : \"dofusjapan\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"de\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"en\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"es\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"it\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"ja\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"nl\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"pt\", \"optional\" : true }, { \"activated\" : false, \"name\" : \"ru\", \"optional\" : true } ] }";
        socket.send(boost::asio::buffer(answer, strlen(answer)));
    }
}