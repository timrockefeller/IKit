#pragma once
#include <mutex>

namespace KTKR {
template <typename T>
class Singleton {
   private:
    /* data */
   public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    virtual ~Singleton() = default;

    const Singleton& operator=(const Singleton&) = delete;
    const Singleton& operator=(Singleton&&) = delete;
    static T& Get() {
        static std::once_flag flag;
        std::call_once(flag, &Singleton::GetInstance);
        return GetInstance();
    }

   protected:
    Singleton() {}

   private:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
};

}  // namespace KTKR
