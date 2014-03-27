#include "sessions/session_server.hpp"
#include "sessions/session_client.hpp"

#include "akm/io/BinaryReader.hpp"
#include "akm/io/BinaryWriter.hpp"
#include "akm/io/BooleanByteWrapper.hpp"

#include "akm/dofus/packet.hpp"

#include "master.hpp"
//#include <stdio.h>

void session_server::handle()
{
    m_buffer.insert(m_buffer.end(), buffer.data(), buffer.data() + size);
    std::shared_ptr<session_client> main_session = master::instance().get_master_client()->get_session(0);

    akm::io::BinaryReader data(m_buffer);
    akm::dofus::Packet packet(&data);

    while (packet.parse())
    {
        packet_data last_packet = packet.getPacketData();
        int lenght = sizeof(short) + last_packet.messageLenghtType + last_packet.messageLength;

        akm::logger::debug() << get_tag() << "ID: " << last_packet.messageId << " Lenght Type: " << last_packet.messageLenghtType << " Lenght: " << last_packet.messageLength;

        akm::io::BinaryWriter output;

        if (last_packet.messageId == 22)
        {
            akm::io::BinaryWriter ism;

            char box0 = 0;
            box0 = akm::io::BooleanByteWrapper::SetFlag(box0, 0, true);
            box0 = akm::io::BooleanByteWrapper::SetFlag(box0, 1, false);

            ism.WriteByte(box0);
            ism.WriteBytes(&last_packet.messageData[1], last_packet.messageLength);

            akm::dofus::Packet::serialize(&output, last_packet.messageId, ism.getBuffer(), ism.getIndex() - 1);
        }
        else
        {
            akm::dofus::Packet::serialize(&output, last_packet);
        }
        
        main_session->write(output.getBuffer(), output.getIndex());

        for (int i = 0; i < lenght; i++)
            m_buffer.pop_front();
    }
}

void::session_server::close()
{
    session::close();

    std::shared_ptr<session_client> main_session = master::instance().get_master_client()->get_session(0);
    main_session->close();
}