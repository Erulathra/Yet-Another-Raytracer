#pragma once
#include <cstdint>
#include <vector>

#include "Defines.h"
#include "Math/LinearMath.h"

namespace YAR {
    class Camera {
    protected:
        Vector3 position;
        Vector3 direction;

    public:
        Camera(const Vector3& position, const Vector3& direction)
            : position(position)
              , direction(direction) {
        }

        virtual ~Camera() = default;

        virtual Ray GetRay(uint32_t X, uint32_t Y, uint32_t ResX, uint32_t ResY) = 0;
    };

    class OrthoCamera : Camera {
        flt orthoSizeX;
        flt orthoSizeY;
    public:
        OrthoCamera(const Vector3& position, const Vector3& direction, flt orthoSizeX, flt orthoSizeY)
            : Camera(position, direction)
              , orthoSizeX(orthoSizeX)
              , orthoSizeY(orthoSizeY) {
        }

        Ray GetRay(uint32_t X, uint32_t Y, uint32_t ResX, uint32_t ResY) override;
    };

    class PerspectiveCamera : Camera {
        flt fov;
        flt nearClip;
    public:
        PerspectiveCamera(const Vector3& position, const Vector3& direction, flt fov, flt nearClip)
            : Camera(position, direction)
            , fov(fov)
            , nearClip(nearClip) {
        }

        Ray GetRay(uint32_t X, uint32_t Y, uint32_t ResX, uint32_t ResY) override;
    };
}
