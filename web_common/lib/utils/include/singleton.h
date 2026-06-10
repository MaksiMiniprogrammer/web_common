#pragma once

#ifndef WEB_COMMON_LIB_UTILS_SINGLETON_H_
#define WEB_COMMON_LIB_UTILS_SINGLETON_H_

#include <boost/core/noncopyable.hpp> 

namespace web
{
namespace utils
{

/**
 * @brief Базовый класс для реализации паттерна Синглтон через CRTP.
 * @tparam T Класс-наследник, который должен стать синглтоном.
 */
template <typename T>
class Singleton : private boost::noncopyable
{
public:
    /**
     * @brief Получить ссылку на единственный экземпляр класса.
     */
    static T& GetInstance() 
    {
        static T instance; 
        return instance;
    }

protected:

    Singleton() = default;
    ~Singleton() = default;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

} // namespace utils
} // namespace web

#endif