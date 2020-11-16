#pragma once
#include <IKit/Pooling/Pool.h>
#include "Entity.h"
#include "details/Chunk.h"
#include "details/Archetype.h"
namespace KTKR::ECS {
class World;
class EntityManager {
   public:
    EntityManager()
        : sharedChunkPool{std::make_unique<Pool<Chunk>>()} {}
    EntityManager(const EntityManager& e)
        : sharedChunkPool{std::make_unique<Pool<Chunk>>()} {}

    Entity Create();

    size_t GenEntitiesFreeIndex();

   private:
    friend class World;

    struct EntityInfo {
        Archetype* archetype{nullptr}; // a list of [Archetype]
        size_t idxInArchetype{static_cast<size_t>(-1)};
        size_t version{0};  // version
    };

    std::vector<EntityInfo> entityTable;
    std::vector<size_t> entityFreeIndexs;

    std::unique_ptr<Pool<Chunk>> sharedChunkPool;
};

}  // namespace KTKR::ECS
