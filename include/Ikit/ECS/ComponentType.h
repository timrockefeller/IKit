#pragma once

#include <set>
/*
    Component Type
*/
namespace KTKR::ECS {
class ComponentType {
   private:
    size_t hash;

   public:
    ComponentType(/* args */);
    ~ComponentType();

    constexpr size_t Hash() const noexcept { return hash; }

    template <typename Cmpt>
    constexpr bool Is() const noexcept {
        static_assert(!IsTaggedCmpt_v<Cmpt>);
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
};
using ComponentTypeObSet = std::set<ComponentTypeOb, std::less<>>;
}  // namespace KTKR::ECS
