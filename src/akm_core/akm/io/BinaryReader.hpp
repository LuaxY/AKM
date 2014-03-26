#ifndef BINARY_READER_HPP
#define BINARY_READER_HPP

#include <vector>
#include <deque>
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

    BinaryReader(const std::deque<char> buffer) :
        m_index(0)
    {
        m_buffer.reserve(buffer.size());
        std::copy(buffer.begin(), buffer.end(), std::back_inserter(m_buffer));
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

    void reverseBytes(uint8_t * bytes, size_t count)
    {
        for (size_t lo = 0, hi = count - 1; hi > lo; ++lo, --hi)
        {
            auto temp = bytes[hi];
            bytes[hi] = bytes[lo];
            bytes[lo] = temp;
        }
    }

    void readBytes(uint8_t* bytes, size_t count)
    {
        memcpy(bytes, &m_buffer[m_index], count);
        m_index += count;
    }

    template<class T>
    void read(T& val)
    {
        readBytes(reinterpret_cast<uint8_t*>(&val), sizeof(T));
        reverseBytes(reinterpret_cast<uint8_t*>(&val), sizeof(T));
    }

    template<class T>
    void read(std::vector<T>& val)
    {
        uint16_t size;
        read(size);
        val.resize(size);
        readBytes(reinterpret_cast<uint8_t *>(&val[0]), size);
    }

    signed short ReadShort()
    {
        signed short value = 0;
        read(value);
        return value;
    }

    unsigned short ReadUShort()
    {
        unsigned short value = 0;
        read(value);
        return value;
    }

    signed int ReadInt()
    {
        signed int value = 0;
        read(value);
        return value;
    }

    unsigned int ReadUInt()
    {
        unsigned int value = 0;
        read(value);
        return value;
    }

    signed long ReadLong()
    {
        signed int value = 0;
        read(value);
        return value;
    }

    unsigned long ReadULong()
    {
        unsigned int value = 0;
        read(value);
        return value;
    }

    char ReadByte()
    {
        char value = m_buffer[m_index];

        m_index++;
        return value;
    }

    char* ReadBytes(int len)
    {
        char* value = new char[len + 1];
        int i;

        for (i = 0; i < len; i++)
            value[i] = m_buffer[m_index + i];
        value[i] = 0;

        m_index += len;
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