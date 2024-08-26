#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

class SHA1
{
public:
    SHA1() { reset(); }
    void update(const std::string &s);
    std::string final();

private:
    void reset();
    void processBlock(const uint8_t *block);
    void processBuffer();

    uint32_t h0, h1, h2, h3, h4;
    uint64_t messageLength;
    std::vector<uint8_t> buffer;
};

void SHA1::reset()
{
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;
    messageLength = 0;
    buffer.clear();
}

void SHA1::update(const std::string &s)
{
    buffer.insert(buffer.end(), s.begin(), s.end());
    messageLength += s.size() * 8;
    while (buffer.size() >= 64)
    {
        processBlock(buffer.data());
        buffer.erase(buffer.begin(), buffer.begin() + 64);
    }
}

std::string SHA1::final()
{
    buffer.push_back(0x80);
    while (buffer.size() % 64 != 56)
    {
        buffer.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i)
    {
        buffer.push_back(static_cast<uint8_t>((messageLength >> (i * 8)) & 0xFF));
    }

    processBuffer();

    std::ostringstream result;
    result << std::hex << std::setfill('0');
    result << std::setw(8) << h0 << std::setw(8) << h1 << std::setw(8) << h2 << std::setw(8) << h3 << std::setw(8) << h4;
    return result.str();
}

void SHA1::processBlock(const uint8_t *block)
{
    uint32_t w[80];
    for (int i = 0; i < 16; ++i)
    {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }
    for (int i = 16; i < 80; ++i)
    {
        w[i] = (w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]);
        w[i] = (w[i] << 1) | (w[i] >> 31);
    }

    uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;
    for (int i = 0; i < 80; ++i)
    {
        uint32_t f, k;
        if (i < 20)
        {
            f = (b & c) | ((~b) & d);
            k = 0x5A827999;
        }
        else if (i < 40)
        {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        else if (i < 60)
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        else
        {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = temp;
    }

    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
}

void SHA1::processBuffer()
{
    while (buffer.size() >= 64)
    {
        processBlock(buffer.data());
        buffer.erase(buffer.begin(), buffer.begin() + 64);
    }
}