#pragma once
#include <Ikit/Pooling/Pool.h>
#include <vector>
#include "Chunk.h"

namespace KTKR::ECS
{
    class Archetype
    {
    public:
        Archetype(/* args */);

        // disable copying
        Archetype(const Archetype &) = delete;
        Archetype &operator=(const Archetype &) = delete;
        ~Archetype();

        void At();
        Chunk *GetChunk(size_t idx) const { return idx < chunks.size() ? chunks[idx] : nullptr; }

    private:
        size_t chunkCapacity{static_cast<size_t>(-1)};
        Pool<Chunk> chunkPool;
        std::vector<Chunk *> chunks;
    };

} // namespace KTKR::ECS
