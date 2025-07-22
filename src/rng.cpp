#include "rng.hpp"

#include <random>

namespace rng {

static std::mt19937 s_Engine;

void Init() {
    std::random_device Device;
    s_Engine.seed(Device());
}

int UniformInt(int Lower, int Upper) {
    std::uniform_int_distribution<int> Dist(Lower, Upper);
    return Dist(s_Engine);
}

}