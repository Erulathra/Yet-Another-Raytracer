#pragma once
#include <cstdint>

#include "Defines.h"
#include "LinearMath.h"

namespace YAM{
    class Random;
}

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
        virtual YAM::Ray GetRay(uint32_t X, uint32_t Y, const YAM::Random& random) const = 0;
    };

    class OrthoCamera : public Camera {
        YAM::flt orthoSizeX;
        YAM::flt orthoSizeY;

    public:
        OrthoCamera(int32_t resolutionX, int32_t resolutionY,
                    const YAM::Vector3& position, const YAM::Vector3& direction,
                    YAM::flt orthoSizeX, YAM::flt orthoSizeY);

        ~OrthoCamera() override;

        YAM::Ray GetRay(uint32_t x, uint32_t y, const YAM::Random& random) const override;
    };

    class PerspectiveCamera : public Camera {
        YAM::flt nearPlaneDistance;

        YAM::Vector3 screenPosition;

        YAM::flt nearPlaneWidth;
        YAM::flt nearPlaneHeight;

    public:
        PerspectiveCamera(int32_t resolutionX, int32_t resolutionY,
                          const YAM::Vector3& position, const YAM::Vector3& direction,
                          YAM::flt nearPlaneDistance);

        ~PerspectiveCamera() override;

        YAM::Ray GetRay(uint32_t x, uint32_t y, const YAM::Random& random) const override;

    private:
        YAM::Vector3 GetScreenPosition() const;
        void CalculateNearPlane(YAM::flt& nearPlaneWidth, YAM::flt& nearPlaneHeight) const;
    };
}
