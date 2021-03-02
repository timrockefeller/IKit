#pragma once

#include <Ikit/Template/TypeID.h>
#include <set>
#include "ComponentTag.h"
/*
    Component Type
*/
namespace KTKR::ECS {
class ComponentType {
   public:
   private:
    size_t hash;

   public:
    explicit constexpr ComponentType(size_t id) noexcept
        : hash{id} {}
    explicit constexpr ComponentType() noexcept
        : ComponentType{Invalid()} {}

    constexpr size_t Hash() const noexcept { return hash; }

    static constexpr ComponentType Invalid() noexcept { return ComponentType{static_cast<size_t>(-1)}; }
    constexpr bool Valid() const noexcept { return hash == static_cast<size_t>(-1); }

    template <typename Cmpt>
    constexpr bool Is() const noexcept {
        // static_assert(!IsTaggedCmpt_v<Cmpt>);
        return hash == TypeID<Cmpt>;
    }

    constexpr bool operator<(const ComponentType& rhs) const noexcept { return hash < rhs.hash; }
    constexpr bool operator<=(const ComponentType& rhs) const noexcept { return hash <= rhs.hash; }
    constexpr bool operator>(const ComponentType& rhs) const noexcept { return hash > rhs.hash; }
    constexpr bool operator>=(const ComponentType& rhs) const noexcept { return hash >= rhs.hash; }
    constexpr bool operator==(const ComponentType& rhs) const noexcept { return hash == rhs.hash; }
    constexpr bool operator!=(const ComponentType& rhs) const noexcept { return hash != rhs.hash; }
};

class ComponentTypeOb {
   public:
    constexpr ComponentTypeOb(size_t id, AccessMode mode) noexcept
        : type{id}, mode{mode} {}
    constexpr ComponentTypeOb(ComponentType type, AccessMode mode) noexcept
        : type{type}, mode{mode} {}
    explicit constexpr ComponentTypeOb(ComponentType type) noexcept
        : ComponentTypeOb{type, AccessMode::EXCLUDE} {}
    explicit constexpr ComponentTypeOb() noexcept
        : ComponentTypeOb{Invalid()} {}

    constexpr AccessMode GetAccessMode() const noexcept { return mode; }
    static constexpr ComponentTypeOb Invalid() noexcept { return ComponentTypeOb{static_cast<size_t>(-1), AccessMode::EXCLUDE}; }
    constexpr bool Valid() const noexcept { return type.Valid(); }

    /** @brief operations */
    constexpr bool operator<(const ComponentTypeOb& rhs) const noexcept { return type < rhs.type; }
    constexpr bool operator<=(const ComponentTypeOb& rhs) const noexcept { return type <= rhs.type; }
    constexpr bool operator>(const ComponentTypeOb& rhs) const noexcept { return type > rhs.type; }
    constexpr bool operator>=(const ComponentTypeOb& rhs) const noexcept { return type >= rhs.type; }
    constexpr bool operator==(const ComponentTypeOb& rhs) const noexcept { return type == rhs.type; }
    constexpr bool operator!=(const ComponentTypeOb& rhs) const noexcept { return type != rhs.type; }
    constexpr bool operator<(const ComponentType& rhs) const noexcept { return type < rhs; }
    constexpr bool operator<=(const ComponentType& rhs) const noexcept { return type <= rhs; }
    constexpr bool operator>(const ComponentType& rhs) const noexcept { return type > rhs; }
    constexpr bool operator>=(const ComponentType& rhs) const noexcept { return type >= rhs; }
    constexpr bool operator==(const ComponentType& rhs) const noexcept { return type == rhs; }
    constexpr bool operator!=(const ComponentType& rhs) const noexcept { return type != rhs; }
    friend constexpr bool operator<(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs < rhs.type; }
    friend constexpr bool operator<=(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs <= rhs.type; }
    friend constexpr bool operator>(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs > rhs.type; }
    friend constexpr bool operator>=(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs >= rhs.type; }
    friend constexpr bool operator==(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs == rhs.type; }
    friend constexpr bool operator!=(const ComponentType& lhs, const ComponentTypeOb& rhs) noexcept { return lhs != rhs.type; }

   private:
    ComponentType type;
    AccessMode mode;
};
using ComponentTypeObSet = std::set<ComponentTypeOb, std::less<>>;
}  // namespace KTKR::ECS
