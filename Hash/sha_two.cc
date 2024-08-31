#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <cstdint>

// Constants and initial hash values
const std::array<uint32_t, 64> K = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f11151, 0x923f82a4, 0xab1c5ed5,
                                    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                                    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7984aa, 0x5cb0a9dc, 0x76f988da,
                                    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6a00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                                    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x82722c85,
                                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                                    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x39100cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cca0208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

const std::array<uint32_t, 8> H0 = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e027f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

// Helper functions for SHA-256 operations
uint32_t rightRotate(uint32_t value, unsigned int count)
{
    return (value >> count) | (value << (32 - count));
}

uint32_t Sigma0(uint32_t x)
{
    return rightRotate(x, 2) ^ rightRotate(x, 13) ^ rightRotate(x, 22);
}

uint32_t Sigma1(uint32_t x)
{
    return rightRotate(x, 6) ^ rightRotate(x, 11) ^ rightRotate(x, 25);
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

// SHA-256 implementation
std::array<uint32_t, 8> sha256(const std::vector<uint8_t> &data)
{
    // Pre-processing: Padding and parsing
    // ...

    // Initialize hash values
    std::array<uint32_t, 8> H = H0;

    // Process each 512-bit block
    for (size_t i = 0; i < data.size(); i += 64)
    {
        std::array<uint32_t, 64> W = {/* Message schedule */};
        // Compression function
        uint32_t a = H[0], b = H[1], c = H[2], d = H[3];
        uint32_t e = H[4], f = H[5], g = H[6], h = H[7];

        for (int t = 0; t < 64; ++t)
        {
            uint32_t T1 = h + Sigma1(e) + Ch(e, f, g) + K[t] + W[t];
            uint32_t T2 = Sigma0(a) + Maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // Update hash values
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }

    return H;
}

int main()
{
    std::vector<uint8_t> data = {1, 2, 3, 4};
    std::array<uint32_t, 8> hash = sha256(data);

    for (uint32_t value : hash)
    {
        std::cout << std::hex << value;
    }
    return 0;
}