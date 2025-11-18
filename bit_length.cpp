#include <climits>

template<typename T>
int bit_length(T x) {
    if (x == 0) return 0;
    int bits = 0;
    while (x > 0) {
        x >>= 1;
        bits++;
    }
    return bits;
}