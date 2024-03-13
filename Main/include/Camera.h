#pragma once
#include <cstdint>
#include <vector>

#include "Defines.h"
#include "LinearMath.h"

namespace YAR{
    class Camera {
    protected:
        YAM::Vector3 position;
        YAM::Vector3 direction;

        uint32_t resolutionX;
        uint32_t resolutionY;

    public:
        Camera(int32_t resolutionX, int32_t resolutionY,
               const YAM::Vector3& position, const YAM::Vector3& direction)
            : position(position)
              , direction(direction)
              , resolutionX(resolutionX)
              , resolutionY(resolutionY) {}

        virtual ~Camera() = default;

        virtual YAM::Ray GetRay(uint32_t X, uint32_t Y) const = 0;
    };

    class OrthoCamera : public Camera {
        flt orthoSizeX;
        flt orthoSizeY;

    public:
        OrthoCamera(int32_t resolutionX, int32_t resolutionY,
                    const YAM::Vector3& position, const YAM::Vector3& direction,
                    flt orthoSizeX, flt orthoSizeY);

        YAM::Ray GetRay(uint32_t x, uint32_t y) const override;
    };

    class PerspectiveCamera : public Camera {
        flt fieldOfView;
        flt nearPlaneDistance;

        YAM::Vector3 screenPosition;

        flt nearPlaneWidth;
        flt nearPlaneHeight;

    public:
        PerspectiveCamera(int32_t resolutionX, int32_t resolutionY,
                          const YAM::Vector3& position, const YAM::Vector3& direction,
                          flt fieldOfView, flt nearPlaneDistance);

        YAM::Ray GetRay(uint32_t x, uint32_t y) const override;

    private:
        YAM::Vector3 GetScreenPosition() const;
        void CalculateNearPlane(flt& nearPlaneWidth, flt& nearPlaneHeight) const;
    };
}
