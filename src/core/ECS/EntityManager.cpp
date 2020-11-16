#include <Ikit/ECS/EntityManager.h>
using namespace KTKR::ECS;
using namespace std;

Entity EntityManager::Create() {
    Entity entity;
    entity.idx = GenEntitiesFreeIndex();
    return entity;
}

size_t EntityManager::GenEntitiesFreeIndex() {
    if (entityFreeIndexs.empty()) {
        size_t entry = entityTable.size();
        entityFreeIndexs.emplace_back();


        return entry;
    }
    size_t entry = entityFreeIndexs.back();
    entityFreeIndexs.pop_back();
    return entry;
}
