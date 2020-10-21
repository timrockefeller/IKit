#include <IKit/ECS/details/Chunk.h>
#include <iostream>
using namespace std;
using namespace KTKR::ECS;
int main() {
    Chunk::Layout layout = Chunk::GenLayout({1, 1, 2, 3, 4, 4, 8}, {1, 1, 2, 3, 3, 4, 7});
    // align:  1, 1, 2, 3, 4, 4, 8
    // size:   1, 1, 2, 3, 3, 4, 7
    // offset: 0, 1, 2, 6,12,16,24
    layout.DebugLog();
    return 0;
}
