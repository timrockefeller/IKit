#include <iostream>
using namespace std;
int main() {
    size_t n = 1024;

    size_t ou1 = static_cast<size_t>(n % -3 > 0);

    size_t ou2 = n % -3 > 0;

    cout << ou1 << " " << ou2;

    return 0;
}
