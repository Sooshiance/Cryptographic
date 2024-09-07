#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>

bool is_prime(std::int32_t num)
{
    if (num < 2)
    {
        return false;
    }
    for (std::int32_t i = 2; i <= sqrt(num); i++)
    {
        // If there is even one number can divided `num`
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

std::int32_t gcd(std::int32_t a, std::int32_t b)
{
    // Dynamic way of finding GCD
    while (b != 0)
    {
        std::int32_t temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

std::int32_t mod_inverse(std::int32_t a, std::int32_t m)
{
    std::int32_t m0 = m, x0 = 0, x1 = 1;

    while (a > 1)
    {
        std::int32_t q = a / m;
        std::int32_t temp = m;

        m = a % m;
        a = temp;

        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }

    return x1 + m0 * (x1 < 0 ? 1 : 0);
}

std::pair<std::pair<std::int32_t, std::int32_t>, std::pair<std::int32_t, std::int32_t>> generate_key_pair(std::int32_t p, std::int32_t q)
{
    std::int32_t n = p * q;
    std::int32_t phi = (p - 1) * (q - 1);

    // Encryption key
    std::int32_t e;

    do
    {
        std::cout << "Enter public key exponent (e): ";
        std::cin >> e;
    } while (gcd(e, phi) != 1);

    // Decryption key
    std::int32_t d = mod_inverse(e, phi);

    return std::make_pair(std::make_pair(e, n), std::make_pair(d, n));
}