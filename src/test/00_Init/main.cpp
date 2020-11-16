
#include <iostream>

#include <vector>

struct foo {};
struct bar {};
void creating_and_assigning() {
    std::tuple<foo, bar, int> t0{{}, {}, 1};
    auto t1 = std::make_tuple(foo{}, bar{}, 5);

    t0 = t1;
    t1 = std::move(t0);
}
void retrieving_by_index() {
    auto t = std::make_tuple(foo{}, bar{}, 5);

    // Getting lvalue references
    foo& i0 = std::get<0>(t);
    bar& i1 = std::get<1>(t);
    int& i2 = std::get<2>(t);

    // Moving out of a tuple
    foo m0 = std::move(std::get<0>(t));
    bar m1 = std::get<1>(std::move(t));
}

void retriving_by_type() {
    auto t = std::make_tuple(foo{}, bar{}, 5);
    const auto& i = std::get<int>(t);
    //assert(i == 5);
}

void apply_example (){
    std::apply([](int x, int y) -> int { return x + y; },
               std::make_tuple(1, 2));
}

int main() {
    return 0;
}
