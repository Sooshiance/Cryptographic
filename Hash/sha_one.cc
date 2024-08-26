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