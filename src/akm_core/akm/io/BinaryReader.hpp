#ifndef BINARY_READER_HPP
#define BINARY_READER_HPP

#include <vector>
#include <fstream>
#include <cstring>

namespace akm {
namespace io {

class BinaryReader
{
public:
    BinaryReader(const char* buffer, int len) :
        m_buffer(buffer, buffer + len),
        m_index(0)
    {
    }

    BinaryReader(const std::vector<char> buffer) :
        m_buffer(buffer),
        m_index(0)
    {
    }

    bool setIndex(unsigned int index)
    {
        if (index >= 0 && index <= m_buffer.size())
        {
            m_index = index;
            return true;
        }

        return false;
    }

    unsigned int getIndex()
    {
        return m_index;
    }

    int bytesAvailable()
    {
        return m_buffer.size() - m_index;
    }

    signed short ReadShort()
    {
        signed short value =
            (signed short)m_buffer[m_index] * 256 +
            (signed short)m_buffer[m_index + 1];

        m_index += 2;
        return value;
    }

    unsigned short ReadUShort()
    {
        unsigned short value =
            (unsigned short)m_buffer[m_index] * 256 +
            (unsigned short)m_buffer[m_index + 1];

        m_index += 2;
        return value;
    }

    char ReadByte()
    {
        char value = (char)m_buffer[m_index];

        m_index++;
        return value;
    }
    char* ReadBytes(unsigned int len)
    {
        char* value = new char[len + 1];
        int i;
        
        for (i = 0; i < len; i++)
            value[i] = m_buffer[m_index + i];
        value[i] = 0;

        m_index += len;
        return value;
    }

    signed int ReadInt()
    {
        signed int value =
            (signed int)m_buffer[m_index] * (256 * 3) +
            (signed int)m_buffer[m_index + 1] * (256 * 2) +
            (signed int)m_buffer[m_index + 2] * (256 * 1) +
            (signed int)m_buffer[m_index + 3];

        m_index += 4;
        return value;
    }

    unsigned int ReadUInt()
    {
        unsigned int value =
            (unsigned int)m_buffer[m_index] * (256 * 3) +
            (unsigned int)m_buffer[m_index + 1] * (256 * 2) +
            (unsigned int)m_buffer[m_index + 2] * (256 * 1) +
            (unsigned int)m_buffer[m_index + 3];

        m_index += 4;
        return value;
    }

    signed long ReadLong()
    {
        signed int value =
            (signed int)m_buffer[m_index] * (256 * 7) +
            (signed int)m_buffer[m_index + 1] * (256 * 6) +
            (signed int)m_buffer[m_index + 2] * (256 * 5) +
            (signed int)m_buffer[m_index + 3] * (256 * 4) +
            (signed int)m_buffer[m_index + 4] * (256 * 3) +
            (signed int)m_buffer[m_index + 5] * (256 * 2) +
            (signed int)m_buffer[m_index + 6] * (256 * 1) +
            (signed int)m_buffer[m_index + 7];

        m_index += 8;
        return value;
    }

    unsigned long ReadULong()
    {
        unsigned int value =
            (unsigned int)m_buffer[m_index] * (256 * 7) +
            (unsigned int)m_buffer[m_index + 1] * (256 * 6) +
            (unsigned int)m_buffer[m_index + 2] * (256 * 5) +
            (unsigned int)m_buffer[m_index + 3] * (256 * 4) +
            (unsigned int)m_buffer[m_index + 4] * (256 * 3) +
            (unsigned int)m_buffer[m_index + 5] * (256 * 2) +
            (unsigned int)m_buffer[m_index + 6] * (256 * 1) +
            (unsigned int)m_buffer[m_index + 7];

        m_index += 8;
        return value;
    }

    char* ReadUTF()
    {
        unsigned short len = ReadUShort();
        return ReadBytes(len);
    }

    char* ReadUTFBytes(unsigned int len)
    {
        return ReadBytes(len);
    }

    bool ReadBool()
    {
        return ReadByte() == 1 ? true : false;
    }

private:
    std::vector<char>   m_buffer;
    unsigned int        m_index;
};


} // namespace network
} // namespace akm

#endif // BINARY_READER_HPP