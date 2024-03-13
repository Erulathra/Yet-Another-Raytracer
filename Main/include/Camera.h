#pragma once
#include <cstdint>
#include <vector>

#include "Defines.h"
#include "LinearMath.h"

namespace YAM {
    class Camera {
    protected:
        Vector3 position;
        Vector3 direction;

        uint32_t ResX;
        uint32_t ResY;

    public:
        Camera(const Vector3& position, const Vector3& direction)
            : position(position)
              , direction(direction)
        , ResX(480)
        , ResY(320) {
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

        Vector3 screenPosition;

        flt screenSizeX;
        flt screenSizeY;
    public:
        PerspectiveCamera(const Vector3& position, const Vector3& direction, flt fov, flt nearClip)
            : Camera(position, direction)
            , fov(fov)
            , nearClip(nearClip) {
            screenPosition = GetScreenPosition();
        }

        Ray GetRay(uint32_t X, uint32_t Y, uint32_t ResX, uint32_t ResY) override;

    private:
        Vector3 GetScreenPosition() const;
        void GetWorldScreenSize(flt& screenSizeX, flt& screenSizeY) const ;
    };
}
