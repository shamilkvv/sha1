#include <iostream>

template <typename T>

T leftСyclicShift(T value, int positions) {
    const int bitSize = sizeof(T) * 8;
    return (value << positions) | (value >> (bitSize - positions));
}

int main() {
   

    return 0;
}