#pragma once
namespace KTKR
{
    template <typename T>
    class Singleton
    {
    public:
        Singleton(const Singleton &) = delete;
        Singleton(Singleton &&) = delete;

        const Singleton &operator=(const Singleton &) = delete;
        const Singleton &operator=(Singleton &&) = delete;
        static T* Get()
        {
            static T* instance = new T;
            return instance;
        }
        virtual ~Singleton() = default;
        Singleton() = default;
    };

} // namespace KTKR