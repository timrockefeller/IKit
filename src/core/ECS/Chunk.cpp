#include <Ikit/ECS/details/Chunk.h>
using namespace KTKR::ECS;
using namespace std;

Chunk::Layout Chunk::GenLayout(const std::vector<size_t>& alignments,
                               const std::vector<size_t>& sizes) noexcept {
    Chunk::Layout layout;
    const size_t SIZE = sizes.size();
    struct Item {
        size_t align;
        size_t idx;
        bool operator<(const Item& rhs) const noexcept {
            return align < rhs.align;
        }
    };

    vector<Item> items(SIZE);
    for (size_t i = 0; i < SIZE; i++)
        items[i] = Item{alignments[i], i};
    sort(items.begin(), items.end());  // 1 1 1 2 2 4 4 8
    size_t sumSize = 0;
    for (size_t s : sizes)
        sumSize += s;
    layout.capacity = 32 / sumSize;

    layout.offsets.resize(SIZE);
    size_t curOffset = 0;
    for (size_t i = 0; i < SIZE; i++) {
        curOffset = items[i].align * ((curOffset + items[i].align - 1) / items[i].align);
        layout.offsets[items[i].idx] = curOffset;
        curOffset += sizes[items[i].idx] * layout.capacity;
    }

    return layout;
}
