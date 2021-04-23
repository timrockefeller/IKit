#include <IKit/ECS/details/Chunk.h>
#include <Ikit/Template/Typelist.h>
#include <Ikit/STL/ILog.h>
#include <iostream>
using namespace std;
int main() {
    // KTKR::ECS::Chunk::Layout layout = KTKR::ECS::Chunk::GenLayout({1, 1, 2, 3, 4, 4, 8}, {1, 1, 2, 3, 3, 4, 7});
    // // align:  1, 1, 2, 3, 4, 4, 8
    // // size:   1, 1, 2, 3, 3, 4, 7
    // // offset: 0, 1, 2, 6,12,16,24
    // layout.DebugLog();

    // =================================================
    using F = KTKR::IValue<bool, true>;
    using T = KTKR::TypeList<int, bool>;

    static_assert(!KTKR::IsTypeList_v<F>);
    static_assert(KTKR::IsTypeList_v<T>);
    static_assert(KTKR::Length_v<T> == 2);

    // =================================================

    using R = KTKR::At_t<T, 1>;
    static_assert(std::is_same_v<R, bool>);
    static_assert(KTKR::Find_v<T, bool> == 1);

    // =================================================

    KTKR::ILog(KTKR::LOG_DEBUG,KTKR::LOG_DEBUG,"Hello, %d", 2);


    return 0;
}
