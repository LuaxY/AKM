#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <sstream>

namespace akm {
namespace logger {

enum verbosity { LOW, MEDIUM, HIGHT };

enum color
{
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    DARK_AQUA = 3,
    DARK_CYAN = 3,
    DARK_RED = 4,
    DARK_PURPLE = 5,
    DARK_PINK = 5,
    DARK_MAGENTA = 5,
    DARK_YELLOW = 6,
    DARK_WHITE = 7,
    GRAY = 8,
    BLUE = 9,
    GREEN = 10,
    AQUA = 11,
    CYAN = 11,
    RED = 12,
    PURPLE = 13,
    PINK = 13,
    MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15,
    DEFAULT = 7,
};

class logger
{
public:
    ~logger();

    template<class T>
    logger &operator<<(const T &x)
    {
        message << x;
        return *this;
    }

    static bool is_filelog;

protected:
    logger(verbosity _level, std::string _tag, color _tag_color) :
        level(_level),
        tag(_tag),
        tag_color(_tag_color)
    {
    }

private:
    std::ostringstream message;
    std::string tag;
    color tag_color;
    verbosity level;

    std::string get_time();

    void set_color(int color);
};

class debug : public logger
{
public:
    debug(verbosity level = LOW) :
        logger(level, "DEBUG", CYAN)
    {}
};

class error : public logger
{
public:
    error(verbosity level = LOW) :
        logger(level, "ERROR", RED)
    {}
};

class info : public logger
{
public:
    info(verbosity level = LOW) :
        logger(level, "INFO", YELLOW)
    {}
};

} // namespace logger
} // namespace akm

#endif // LOGGER_HPP