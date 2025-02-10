#ifndef SINGLETON_H
#define SINGLETON_H

#include "global.h"

template <typename T>
class Singleton {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }

protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;
    static std::shared_ptr<T> _instance;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
