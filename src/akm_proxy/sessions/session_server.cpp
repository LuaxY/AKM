#include "sessions/session_server.hpp"
#include "sessions/session_client.hpp"
#include "akm/dofus/packet.hpp"
#include "akm/io/BinaryReader.hpp"
#include "akm/utils/hexdump.hpp"
#include "master.hpp"
#include <stdio.h>

void session_server::handle()
{
    m_buffer.insert(m_buffer.end(), buffer.data(), buffer.data() + size);
    std::shared_ptr<session_client> main_session = master::instance().get_master_client()->get_session(0);

    akm::io::BinaryReader data(m_buffer);
    akm::dofus::Packet packet(&data);

    while (packet.parse())
    {
        packet_data last_packet = packet.getPacketData();
        akm::logger::debug() << "id: " << last_packet.messageId << " lenght type: " << last_packet.messageLenghtType << " lenght: " << last_packet.messageLength;

        int totalLenght = sizeof(short) + last_packet.messageLenghtType + last_packet.messageLength;
        akm::logger::debug() << "total: " << totalLenght;

        /*for (int i = 0; i < m_packet.messageLength; i++)
            printf("%02X ", 0xFF & m_packet.messageData[i]);
        std::cout << std::endl;*/

        main_session->write(last_packet.messageData, totalLenght);

        for (int i = 0; i < totalLenght; i++)
            m_buffer.pop_front();
    }
}