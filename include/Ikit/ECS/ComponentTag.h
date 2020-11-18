#pragma once
#include <Ikit/Template/Basic.h>
namespace KTKR::ECS {
enum class AccessMode {
    // ref: https://docs.unity3d.com/Packages/com.unity.entities@0.16/api/Unity.Entities.ComponentType.AccessMode.html
    READ_WRITE = 0,
    READ_ONLY = 1,
    EXCLUDE = 2
};

}  // namespace KTKR::ECS
