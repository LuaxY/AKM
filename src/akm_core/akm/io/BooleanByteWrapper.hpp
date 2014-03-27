#ifndef BOOLEAN_BYTE_WRAPPER_HPP
#define BOOLEAN_BYTE_WRAPPER_HPP

namespace akm {
namespace io {

class BooleanByteWrapper
{
public:
    static char SetFlag(char flag, char offset, bool value)
    {
        return value ? (char)(flag | (1 << offset)) : (char)(flag & 255 - (1 << offset));
    }

    static char SetFlag(int flag, char offset, bool value)
    {
        return value ? (char)(flag | (1 << offset)) : (char)(flag & 255 - (1 << offset));
    }

    static bool GetFlag(char flag, char offset)
    {
        return (flag & (char)(1 << offset)) != 0;
    }
};

} // namespace network
} // namespace akm

#endif // BOOLEAN_BYTE_WRAPPER_HPP