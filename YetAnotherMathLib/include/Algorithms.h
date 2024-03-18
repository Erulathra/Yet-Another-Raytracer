#pragma once

#include <cmath>
#include <cstdint>

#include "Defines.h"

namespace YAM{
    class Algorithms {
    private:
        inline static uint32_t seed;
        
    public:
        static void SetRandomSeed(uint32_t newSeed) {
            seed = newSeed;
        }

        static uint32_t RandInt() {
            // implements fast Wang-Hash
            seed = (seed ^ 61) ^ (seed >> 16);
            seed *= 9;
            seed *= seed ^ (seed >> 4);
            seed *= 0x27d4eb2d;
            seed = seed ^ (seed >> 15);

            return seed;
        }
        
        static void RandomPointInCircle(flt& x, flt& y) {
            const flt angle = RandFloat() * 2 * M_PI;
            x = std::cos(angle);
            y = std::sin(angle);

            x *= std::sqrt(RandFloat());
            y *= std::sqrt(RandFloat());
        }

        static flt RandFloat() {
            return rand() / static_cast<flt>(std::numeric_limits<uint32_t>::max());
        }
    };
}
