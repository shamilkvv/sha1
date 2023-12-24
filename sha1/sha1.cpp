#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

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

std::string sha1(const std::string& message) {
    std::vector<bool> messageB;
    for (char c : message) {
        for (int bit = 7; bit >= 0; --bit) {
            messageB.push_back((c & (1 << bit)) != 0);
        }
    }

    unsigned int H[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    unsigned int K[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
    uint64_t messageL = messageB.size();
    messageB.push_back(true);
    while (messageB.size() % 512 != 448) {
        messageB.push_back(false);
    }

    for (int i = 63; i >= 0; --i) {
        messageB.push_back((messageL & (1ULL << i)) != 0);
    }

    for (size_t i = 0; i < messageB.size(); i += 512) {
        unsigned int A = H[0];
        unsigned int B = H[1];
        unsigned int C = H[2];
        unsigned int D = H[3];
        unsigned int E = H[4];

        std::vector<unsigned int> W(80, 0);
        for (size_t j = i, k = 0; j < i + 512; j += 32, ++k) {
            for (int z = j, p = 0; z < j + 32; ++z, ++p) {
                W[k] |= (static_cast<unsigned int>(messageB[z]) << p);
            }
        }

        for (size_t j = 16; j <= 79; ++j) {
            W[j] = leftСyclicShift(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
        }

        for (size_t j = 0; j <= 79; ++j) {
            unsigned int temp = leftСyclicShift(A, 5) + nonLinFunc(j, B, C, D) + E + W[j];
            temp += (j <= 19) ? K[0] : (j <= 39) ? K[1] : (j <= 59) ? K[2] : K[3];
            E = D;
            D = C;
            C = leftСyclicShift(B, 30);
            B = A;
            A = temp;
        }

        H[0] += A;
        H[1] += B;
        H[2] += C;
        H[3] += D;
        H[4] += E;
    }

    std::string res;
    for (unsigned int h : H) {
        char Charss[8];
        std::snprintf(Charss, sizeof(Charss), "%08x", h);
        res += Charss;
    }

    return res;
}

int main() {
    std::string input = "Tyler Durden";
    std::cout << sha1(input) << "\n";

    return 0;
}