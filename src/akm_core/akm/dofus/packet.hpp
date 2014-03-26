#ifndef PACKET_HPP
#define PACKET_HPP

#include "akm/io/BinaryReader.hpp"
#include "akm/io/BinaryWriter.hpp"

typedef struct packet_data
{
    unsigned short messageId;
    unsigned short messageLenghtType;
    unsigned int messageLength;
    char* messageData;
};

namespace akm {
namespace dofus {

class Packet
{
public:
    Packet(akm::io::BinaryReader* data) :
        m_data(data)
    {
    }

    bool parse()
    {
        m_packet.messageId = 0;
        m_packet.messageLenghtType = 0;
        m_packet.messageLength = 0;
        m_packet.messageData = nullptr;

        if (m_data->bytesAvailable() < sizeof(short))
            return false;

        unsigned short staticHeader = m_data->ReadUShort();
        m_packet.messageId = getMessageId(staticHeader);
        m_packet.messageLenghtType = getMessageLenghtType(staticHeader);

        if (m_data->bytesAvailable() < m_packet.messageLenghtType)
            return false;

        m_packet.messageLength = readMessageLenght(m_packet.messageLenghtType);

        if (m_data->bytesAvailable() < m_packet.messageLength)
            return false;

        m_packet.messageData = m_data->ReadBytes(m_packet.messageLength);

        return true;
    }

    unsigned short getMessageId(unsigned short staticHeader)
    {
        return staticHeader >> 2;
    }

    unsigned short getMessageLenghtType(unsigned short staticHeader)
    {
        return staticHeader & 3;
    }

    unsigned short readMessageLenght(unsigned short byteLenghtDynamicHeader)
    {
        unsigned short messageLenght = 0;

        switch (byteLenghtDynamicHeader)
        {
            case 1:
                messageLenght = m_data->ReadByte();
                break;
            case 2:
                messageLenght = m_data->ReadUShort();
                break;
            case 3:
                messageLenght = ((m_data->ReadByte() & 255) << 16) + ((m_data->ReadByte() & 255) << 8) + (m_data->ReadByte() & 255);
                break;
            case 0:
            default:
                break;
        }

        return messageLenght;
    }

    static unsigned short computeTypeLen(unsigned short len)
    {
        if (len > 65535)
            return 3;
        if (len > 255)
            return 2;
        if (len > 0)
            return 1;

        return 0;
    }

    static unsigned short subComputeStaticHeader(unsigned short msgId, unsigned short typeLen)
    {
        return msgId << 2 | typeLen;
    }

    packet_data getPacketData()
    {
        return m_packet;
    }

    static void serialize(akm::io::BinaryWriter* output, packet_data packet)
    {
        serialize(output, packet.messageId, packet.messageData, packet.messageLength);
    }

    static void serialize(akm::io::BinaryWriter* output, unsigned short msgId, char* data, unsigned int len)
    {
        unsigned short typeLen = computeTypeLen(len);
        output->WriteUShort(subComputeStaticHeader(msgId, typeLen));

        switch (typeLen)
        {
            case 1:
                output->WriteByte(len);
                break;
            case 2:
                output->WriteUShort(len);
                break;
            case 3:
                // no function for 3 bytes :(
                break;
            case 0:
            default:
                break;
        }

        output->WriteBytes(data, len);
    }

private:
    akm::io::BinaryReader*  m_data;
    packet_data             m_packet;
};

}
}

#endif // PACKET_HPP