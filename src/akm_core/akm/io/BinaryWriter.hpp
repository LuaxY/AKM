#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP

#include <cstring>

namespace akm {
namespace io {

class BinaryWriter
{
public:
    BinaryWriter() :
        m_buffer(new char[8126]),
        m_index(0)
    {
    }

    BinaryWriter(unsigned int len) :
        m_buffer(new char[len]),
        m_index(0)
    {
    }

    ~BinaryWriter()
    {
        delete[] m_buffer;
    }

    void reset()
    {
        delete[] m_buffer;
        m_buffer = new char[8126];
        m_index = 0;
    }

    void reset(int len)
    {
        delete[] m_buffer;
        m_buffer = new char[len];
        m_index = 0;
    }

    unsigned int getIndex()
    {
        return m_index;
    }

    char* getBuffer()
    {
        return m_buffer;
    }

    short SwapShort(short data)
    {
        return (data >> 8) | 
            (data << 8);
    }

    int SwapInt(int data)
    {
        return (data >> 24) | 
            ((data << 8) & 0x00FF0000) | 
            ((data >> 8) & 0x0000FF00) | 
            (data << 24);
    }

    long SwapLong(long data)
    {
        return (data >> 56) | 
            ((data << 40) & 0x00FF000000000000) | 
            ((data << 24) & 0x0000FF0000000000) | 
            ((data << 8) & 0x000000FF00000000) | 
            ((data >> 8) & 0x00000000FF000000) | 
            ((data >> 24) & 0x0000000000FF0000) | 
            ((data >> 40) & 0x000000000000FF00) | 
            (data << 56);
    }

    double SwapDouble(double data)
    {
        int* p = (int*)&data;
        int tmp = p[0];
        p[0] = SwapInt(p[1]);
        p[1] = SwapInt(tmp);

        return data;
    }

    void WriteByte(char data)
    {
        m_buffer[m_index] = data;
        m_index++;
    }

    void WriteBytes(char* data, int len)
    {
        int i;

        for (i = 0; i < len; i++)
            m_buffer[m_index + i] = data[i];

        m_index += i;
    }

    void WriteShort(signed short data)
    {
        data = SwapShort(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteUShort(unsigned short data)
    {
        data = SwapShort(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteInt(signed int data)
    {
        data = SwapInt(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteUInt(unsigned int data)
    {
        data = SwapInt(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteLong(signed long data)
    {
        data = SwapLong(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteULong(unsigned long data)
    {
        data = SwapLong(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteDoube(double data)
    {
        data = SwapDouble(data);
        memcpy(m_buffer + m_index, &data, sizeof(data));
        m_index += sizeof(data);
    }

    void WriteUTF(char* data)
    {
        int i;
        int len = strlen(data);

        WriteUShort((unsigned short)len);

        for (i = 0; i < len; i++)
            m_buffer[m_index + i] = data[i];

        m_index += i;
    }

    void WriteUTFBytes(char* data, int len)
    {
        int i;

        WriteUShort(len);

        for (i = 0; i < len; i++)
            m_buffer[m_index + i] = data[i];

        m_index += i;
    }

    void WriteBool(bool data)
    {
        if (data)
            WriteByte(1);
        else
            WriteByte(0);
    }

private:
    char*         m_buffer;
    unsigned int  m_index;
};


} // namespace network
} // namespace akm

#endif // BINARY_WRITER_HPP