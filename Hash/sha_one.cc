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