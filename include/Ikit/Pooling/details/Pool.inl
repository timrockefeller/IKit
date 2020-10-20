#pragma once
#include <array>
#include <cstdlib>
#include <unordered_set>

namespace KTKR {
template <typename T, size_t BLOCK_SIZE>
Pool<T, BLOCK_SIZE>::Pool(Pool&& pool) noexcept
    : blocks(std::move(pool.blocks)), frees(std::move(pool.frees)) {
    pool.blocks.clear();
    pool.frees.clear();
}

template <typename T, size_t BLOCK_SIZE>
Pool<T, BLOCK_SIZE>::~Pool() {
    Clear();
}

template <typename T, size_t BLOCK_SIZE>
template <typename... Args>
T* Pool<T, BLOCK_SIZE>::Request(Args&&... args) {
    if (frees.empty())
        NewBlock();
    T* newAdr = frees.back();
    new (newAdr) T(std::forward<Args>(args)...);
    frees.pop_back();
    return newAdr;
}

template <typename T, size_t BLOCK_SIZE>
void Pool<T, BLOCK_SIZE>::Recycle(T* obj) {
    if constexpr (!std::is_trivially_destructible_v<T>)
        obj->~T();
    frees.push_back(obj);
}

template <typename T, size_t BLOCK_SIZE>
void Pool<T, BLOCK_SIZE>::Reserve(size_t n) {
    size_t blockNum = n / BLOCK_SIZE + static_cast<size_t>(n % BLOCK_SIZE > 0);
    for (size_t i = blocks.size(); i < blockNum; i++)
        NewBlock();
}

template <typename T, size_t BLOCK_SIZE>
void Pool<T, BLOCK_SIZE>::FastClear() {
    for (auto block : blocks)
#ifdef _WIN32
        _aligned_free(block);
#else
        free(block);
#endif
    blocks.clear();
    frees.clear();
}

template <typename T, size_t BLOCK_SIZE>
void Pool<T, BLOCK_SIZE>::Clear() {
    if (std::is_trivially_destructible_v<T>) {
        FastClear();
        return;
    }
    std::unordered_set<T*> freeAdrSets(frees.begin(), frees.end());
    for (auto block : blocks) {
        for (size_t i = 0; i < BLOCK_SIZE; i++) {
            T* adress = block + i;
            if (freeAdrSets.find(adress) == freeAdrSets.end())
                adress->~T();
        }
#ifdef _WIN32
        _aligned_free(block);
#else
        free(block);
#endif
        blocks.clear();
        frees.clear();
    }
}

template <typename T, size_t BLOCK_SIZE>
void Pool<T, BLOCK_SIZE>::NewBlock() {
#ifdef _WIN32
    auto block = reinterpret_cast<T*>(_aligned_malloc(BLOCK_SIZE * sizeof(T), std::alignment_of_v<T>));
#else
    auto block = reinterpret_cast<T*>(aligned_alloc(BLOCK_SIZE * sizeof(T), std::alignment_of_v<T>));
#endif
}
}  // namespace KTKR
