#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <cassert>

namespace akm {
namespace serialization {

template<class T>
class singleton
{
protected:
    singleton() = default;
    ~singleton() = default;

public:
    template<class ... Args>
    static T& create(Args && ... args)
    {
        assert(!_singleton);
        _singleton.reset(new T{ std::forward<Args>(args)... });
        return *_singleton;
    }

    static void kill()
    {
        _singleton.reset(nullptr);
    }

    static T& instance()
    {
        assert(_singleton);
        return *_singleton;
    }

private:
    static std::unique_ptr<T> _singleton;
};

template<class T>
std::unique_ptr<T> singleton<T>::_singleton;

} // namespace serialization
} // namespace akm

#endif // SINGLETON_HPP
