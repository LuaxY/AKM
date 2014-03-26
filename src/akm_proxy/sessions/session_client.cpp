#include "sessions/session_client.hpp"
#include "sessions/session_server.hpp"
#include "master.hpp"

void session_client::init()
{
    master::instance().connect_to_ankama();
}

void session_client::handle()
{
    /*std::shared_ptr<session_server> main_session = master::instance().get_master_server()->get_session(0);
    main_session->write(buffer.data(), size);*/

    m_buffer.insert(m_buffer.end(), buffer.data(), buffer.data() + size);
    std::shared_ptr<session_server> main_session = master::instance().get_master_server()->get_session(0);

    akm::io::BinaryReader data(m_buffer);
    akm::dofus::Packet packet(&data);

    while (packet.parse())
    {
        packet_data last_packet = packet.getPacketData();
        int lenght = sizeof(short)+last_packet.messageLenghtType + last_packet.messageLength;

        akm::io::BinaryWriter output;
        akm::dofus::Packet::serialize(&output, last_packet);

        akm::logger::debug() << get_tag() << "ID: " << last_packet.messageId << " Lenght Type: " << last_packet.messageLenghtType << " Lenght: " << last_packet.messageLength;

        /*for (int i = 0; i < m_packet.messageLength; i++)
        printf("%02X ", 0xFF & m_packet.messageData[i]);
        std::cout << std::endl;*/

        main_session->write(output.getBuffer(), output.getIndex());

        for (int i = 0; i < lenght; i++)
            m_buffer.pop_front();
    }
}