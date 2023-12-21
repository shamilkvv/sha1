#include <iostream>

template <typename T>

T leftСyclicShift(T value, int positions) {
    const int bitSize = sizeof(T) * 8;
    return (value << positions) | (value >> (bitSize - positions));
}

unsigned int nonLinFunc(int i, unsigned int B, unsigned int C, unsigned int D) {
    if (0 <= i && i <= 19) {
        return (B & C) | ((~B) & D);
    }
    else if (20 <= i && i <= 39) {
        return B ^ C ^ D;
    }
    else if (40 <= i && i <= 59) {
        return (B & C) | (B & D) | (C & D);
    }
    else if (60 <= i && i <= 79) {
        return B ^ C ^ D;
    }
    return 0;
}

int main() {
   

    return 0;
}