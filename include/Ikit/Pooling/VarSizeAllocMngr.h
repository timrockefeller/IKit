// ref:
// 1. https://github.com/DiligentGraphics/DiligentCore/blob/master/Graphics/GraphicsAccessories/interface/VariableSizeAllocationsManager.hpp
// 2. http://diligentgraphics.com/diligent-engine/architecture/d3d12/variable-size-memory-allocations-manager/
#pragma once

#include <algorithm>
#include <cassert>
#include <map>
// #include "../../../Primitives/interface/MemoryAllocator.h"
// #include "../../../Platforms/Basic/interface/DebugUtilities.hpp"
// #include "../../../Common/interface/Align.hpp"
// #include "../../../Common/interface/STDAllocator.hpp"
#include "Align.h"
namespace KTKR {
// The class handles free memory block management to accommodate variable-size allocation requests.
// It keeps track of free blocks only and does not record allocation sizes. The class uses two ordered maps
// to facilitate operations. The first map keeps blocks sorted by their offsets. The second multimap keeps blocks
// sorted by their sizes. The elements of the two maps reference each other, which enables efficient block
// insertion, removal and merging.
//
//   8                 32                       64                           104
//   |<---16--->|       |<-----24------>|        |<---16--->|                 |<-----32----->|
//
//
//        m_FreeBlocksBySize      m_FreeBlocksByOffset
//           size->offset            offset->size
//
//                16 ------------------>  8  ---------->  {size = 16, &m_FreeBlocksBySize[0]}
//
//                16 ------.   .-------> 32  ---------->  {size = 24, &m_FreeBlocksBySize[2]}
//                          '.'
//                24 -------' '--------> 64  ---------->  {size = 16, &m_FreeBlocksBySize[1]}
//
//                32 ------------------> 104 ---------->  {size = 32, &m_FreeBlocksBySize[3]}
//
class VarSizeAllocMngr {
   private:
    struct FreeBlockInfo;

    // Type of the map that keeps memory blocks sorted by their offsets
    using TFreeBlocksByOffsetMap = std::map<size_t, FreeBlockInfo>;

    // Type of the map that keeps memory blocks sorted by their sizes
    using TFreeBlocksBySizeMap = std::multimap<size_t, TFreeBlocksByOffsetMap::iterator>;

    struct FreeBlockInfo {
        // Block size (no reserved space for the size of the allocation)
        size_t size;

        // Iterator referencing this block in the multimap sorted by the block size
        TFreeBlocksBySizeMap::iterator OrderBySizeIt;

        FreeBlockInfo(size_t size)
            : size(size) {}
    };

   public:
    VarSizeAllocMngr(size_t capacity)
        : capacity(capacity),
          freeSize(capacity) {
        // Insert single maximum-size block
        AddNewBlock(0, capacity);
        ResetCurrAlignment();
    }

    // clang-format off
        VarSizeAllocMngr(VarSizeAllocMngr&& rhs) noexcept :
            offset2freeblock{ std::move(rhs.offset2freeblock) },
            size2freeblock{ std::move(rhs.size2freeblock) },
            capacity{ rhs.capacity },
            freeSize{ rhs.freeSize },
            curMinAlignment{ rhs.curMinAlignment }
        {
        // clang-format on
        rhs.capacity = 0;
        rhs.freeSize = 0;
        rhs.curMinAlignment = 0;
    }

    // clang-format off
        VarSizeAllocMngr& operator = (VarSizeAllocMngr&& rhs) = default;
        VarSizeAllocMngr(const VarSizeAllocMngr&) = delete;
        VarSizeAllocMngr& operator = (const VarSizeAllocMngr&) = delete;
    // clang-format on

    // Offset returned by Allocate() may not be aligned, but the size of the allocation
    // is sufficient to properly align it
    struct Allocation {
        // clang-format off
            Allocation(size_t offset, size_t size) :
                unalignedOffset{ offset },
                size{ size }
            {}
        // clang-format on

        Allocation() {}

        static constexpr size_t InvalidOffset = static_cast<size_t>(-1);

        static Allocation InvalidAllocation() {
            return Allocation{InvalidOffset, 0};
        }

        bool IsValid() const {
            return unalignedOffset != InvalidAllocation().unalignedOffset;
        }

        size_t unalignedOffset = InvalidOffset;
        size_t size = 0;
    };

    Allocation Allocate(size_t size, size_t alignment);

    void Free(Allocation&& allocation) {
        Free(allocation.unalignedOffset, allocation.size);
        allocation = Allocation{};
    }

    void Free(size_t offset, size_t size);

    bool IsFull() const { return freeSize == 0; };
    bool IsEmpty() const { return freeSize == capacity; };
    size_t GetCapacity() const { return capacity; }
    size_t GetFreeSize() const { return freeSize; }
    size_t GetUsedSize() const { return capacity - freeSize; }

    size_t GetNumFreeBlocks() const {
        return offset2freeblock.size();
    }

   private:
    void AddNewBlock(size_t Offset, size_t Size) {
        auto NewBlockIt = offset2freeblock.emplace(Offset, Size);
        assert(NewBlockIt.second);
        auto OrderIt = size2freeblock.emplace(Size, NewBlockIt.first);
        NewBlockIt.first->second.OrderBySizeIt = OrderIt;
    }

    void ResetCurrAlignment() {
        curMinAlignment = 1;
        while (curMinAlignment * 2 <= capacity)
            curMinAlignment *= 2;
    }

    TFreeBlocksByOffsetMap offset2freeblock;
    TFreeBlocksBySizeMap size2freeblock;

    size_t capacity = 0;
    size_t freeSize = 0;
    size_t curMinAlignment = 0;  // min alignment of all free blocks
    // When adding new members, do not forget to update move ctor
};
}  // namespace KTKR
