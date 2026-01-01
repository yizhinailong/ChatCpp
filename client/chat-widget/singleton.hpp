#pragma once

#include <iostream>
#include <memory>
#include <mutex>

template <typename T>
class Singleton {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            m_instance = std::shared_ptr<T>(new T);
        });

        return m_instance;
    }

    void PrintAddress() {
        std::cout << m_instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "This is singleton destruct." << std::endl;
    }

protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>& /* unused */) = delete;

    static std::shared_ptr<T> m_instance;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;
