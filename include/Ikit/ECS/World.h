#pragma once

#include "EntityManager.h"
#include "SystemManager.h"
namespace KTKR::ECS {
class World {
   public:
    World()=default;
    World(const World&)  {}

    EntityManager entityManager;
    SystemManager systemManager;

   private:
};

}  // namespace KTKR::ECS
