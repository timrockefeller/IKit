#pragma once
#include <array>
#include <vector>
#ifdef _DEBUG
#include <iostream>
#endif
#include "config.h"
namespace KTKR::ECS {

 /*
ref:
    1. https://blog.csdn.net/yudianxia/article/details/80498015
    2. https://docs.unity3d.com/Packages/com.unity.entities@0.14/manual/ecs_components.html
*/

/*
desc:
    The EntityManager organizes unique combinations of components into archetypes. 
    It stores the components of all entities with the same archetype together in
    blocks of memory called chunks. 
    The entities in a given chunk all have the same component archetype.
*/
using byte = uint8_t;
static_assert(sizeof(byte) == 1);
struct alignas(CHUNK_ALIGNMENT) Chunk {
    static constexpr size_t size = CHUNK_SIZE;
    struct Layout {
        size_t capacity;
        std::vector<size_t> offsets;
#ifdef _DEBUG
        void DebugLog() {
            std::cout << "[Debug] capacity: ";
            std::cout << capacity << std::endl;
            for (size_t i = 0; i < offsets.size(); i++)
                std::cout << offsets[i] << " ";
        }
#endif
    };

    static Layout GenLayout(
        const std::vector<size_t>& alignments,
        const std::vector<size_t>& sizes) noexcept;

    byte* Data() noexcept { return buffer.data(); }

   private:
    std::array<byte, size> buffer;
};
}  // namespace KTKR::ECS
