#include "randGen.hpp"
uint32_t getRand(const uint32_t& A, const uint32_t& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<uint32_t> dist;

    dist.param(std::uniform_int_distribution<uint32_t>::param_type(A, B));
    return dist(twister);
}