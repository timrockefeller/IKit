#pragma once

// Chunk memory align configs

namespace KTKR::ECS {
constexpr size_t CHUNK_ALIGNMENT = 1 << 6;
constexpr size_t CHUNK_SIZE = 1 << 14;
}  // namespace KTKR::ECS
