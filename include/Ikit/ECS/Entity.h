#pragma once

namespace KTKR::ECS {
class Entity {
   public:
    constexpr Entity(size_t idx, size_t version) noexcept
        : idx(idx), version(idx) {}
    constexpr Entity() noexcept
        : Entity(Invalid()) {}
    static constexpr Entity Invalid() noexcept {
        return {static_cast<size_t>(-1), static_cast<size_t>(-1)};
    }

    constexpr size_t Idx() const noexcept { return idx; }
    constexpr size_t Version() const noexcept { return version; }
    constexpr bool Valid() const noexcept { return idx != static_cast<size_t>(-1); }

    constexpr bool operator==(const Entity& rhs) const noexcept {
        return idx == rhs.idx && version == rhs.version;
    }
    constexpr bool operator<(const Entity& rhs) const noexcept {
        return idx < rhs.idx || (idx == rhs.idx) && version < rhs.version;
    }

   private:
    friend class EntityManager;

    size_t idx;
    size_t version;
};
}  // namespace KTKR::ECS
