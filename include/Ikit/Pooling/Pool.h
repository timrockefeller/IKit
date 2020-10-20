#pragma once
#include <vector>
namespace KTKR {
//      Align memory pooling.

/*
        TYPE            Byte-Boundary
        -----------------------------
        bool            1
        char
        short           2
        int             4
        long
        float
        long long       8
        double
        long double
*/

template <typename T, size_t BLOCK_SIZE = 1024>
class Pool {
   public:
    Pool() = default;
    Pool(Pool&&) noexcept;
    Pool& operator=(Pool&&) noexcept;
    ~Pool();

    template <typename... Args>
    T* Request(Args&&...);
    void Recycle(T*);
    void Reserve(size_t);
    void FastClear();
    void Clear();

   private:
    void NewBlock();

   private:
    std::vector<T*> blocks;
    std::vector<T*> frees;
};
}  // namespace KTKR

#include "details/Pool.inl"
