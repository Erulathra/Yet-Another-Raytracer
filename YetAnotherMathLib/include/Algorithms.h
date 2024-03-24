#pragma once

#include <cmath>
#include <cstdint>

#include "Defines.h"
#include "LinearMath.h"
#include "Vector3.h"

namespace YAM{
    class Algorithms {
    private:


    public:
    };

    class Random {
    private:
        mutable uint32_t seed;

    public:
        explicit Random()
            : Random(time(nullptr)) {}
        
        Random(uint32_t seed) {
            this->seed = seed;
        }


        void SetRandomSeed(uint32_t newSeed) const {
            seed = newSeed;
        }

        uint32_t RandInt() const {
            uint32_t z = seed + 0x9e3779b9;
            z ^= z >> 15; // 16 for murmur3
            z *= 0x85ebca6b;
            z ^= z >> 13;
            z *= 0xc2b2ae35;
            seed = z ^ (z >> 16);
            return seed;
        }

        void RandomPointInCircle(flt& x, flt& y) const {
            const flt angle = RandFloat() * 2. * M_PI;
            const flt radius = std::sqrt(RandFloat());
            
            x = radius * std::cos(angle);
            y = radius * std::sin(angle);
        }

        Vector3 RandomHemisphereDirection(const Vector3& normal) const {
            Vector3 result;
            result.x = RandFloatNormal();
            result.y = RandFloatNormal();
            result.z = RandFloatNormal();

            result = result.Normal();

            if (normal.Dot(result) < 0.f) {
                return result * -1.f;
            }

            return result;
        }
        
        Vector3 RandomDirection() const {
            Vector3 result;
            result.x = RandFloatNormal();
            result.y = RandFloatNormal();
            result.z = RandFloatNormal();

            return result.Normal();
        }

        flt RandFloatNormal() const {
            const flt theta = 2.f * M_PI * RandFloat();
            const flt rho = std::sqrt(-2.f * std::log(RandFloat()));

            return rho * std::cos(theta);
        }

        static constexpr flt one_randMax = 1. / 0xFFFFFFFFU;

        flt RandFloat() const {
            return static_cast<flt>(RandInt()) * one_randMax;
        }
    };
}
