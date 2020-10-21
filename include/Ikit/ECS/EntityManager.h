#pragma once
#include <IKit/Pooling/Pool.h>
#include "details/Chunk.h"
namespace KTKR::ECS {
class World;
class EntityManager {
   public:
    EntityManager() = default;

   private:
    friend class World;
    std::unique_ptr<Pool<Chunk>> sharedChunkPool;
};

}  // namespace KTKR::ECS
