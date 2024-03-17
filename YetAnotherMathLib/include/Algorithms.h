#pragma once

#include <math.h>
#include <cstdlib>

#include "Defines.h"

namespace YAM{
    class Algorithms {
    public:
        static void RandomPointInCircle(flt& x, flt& y) {
            const flt angle = RandFloat() * 2 * M_PI;
            x = std::cos(angle);
            y = std::sin(angle);

            x *= std::sqrt(RandFloat());
            y *= std::sqrt(RandFloat());
        }

        static flt RandFloat() {
            return rand() / static_cast<flt>(RAND_MAX);
        }
    };
}
