#include "Camera.h"

#include "Algorithms.h"

namespace YAR{
    using namespace YAM;

    OrthoCamera::OrthoCamera(int32_t resolutionX, int32_t resolutionY, const YAM::Vector3& position,
                             const YAM::Vector3& direction, flt orthoSizeX, flt orthoSizeY)
        : Camera(resolutionX, resolutionY, position, direction)
          , orthoSizeX(orthoSizeX)
          , orthoSizeY(orthoSizeY) {}

    OrthoCamera::~OrthoCamera() {};

    Ray OrthoCamera::GetRay(uint32_t x, uint32_t y) const {
        const flt stepX = orthoSizeX / resolutionX;
        const flt stepY = orthoSizeY / resolutionY;

        const Vector3 screenRight = -direction.Cross({0., 1., 0.}).Normal();
        const Vector3 screenUp = -direction.Cross(screenRight).Normal();

        const Vector3 screenLeft = -screenRight;
        const Vector3 screenDown = -screenUp;

        Vector3 screenStart = position + (screenLeft * (orthoSizeX * 0.5f))
            + (screenUp * (orthoSizeY * 0.5f));
        
        flt jitterX, jitterY;
        Algorithms::RandomPointInCircle(jitterX, jitterY);
        constexpr flt jitterStrenth = 0.5f;

        Vector3 screenOffset = (stepX * screenRight * (static_cast<flt>(x) + jitterX * jitterStrenth))
                             + (stepY * screenDown * (static_cast<flt>(y) + jitterY * jitterStrenth)); 

        return {direction, screenStart + screenOffset};
    }

    PerspectiveCamera::PerspectiveCamera(int32_t resolutionX, int32_t resolutionY, const YAM::Vector3& position,
                                         const YAM::Vector3& direction, flt nearPlaneDistance)
        : Camera(resolutionX, resolutionY, position, direction)
          , nearPlaneDistance(nearPlaneDistance)
          , nearPlaneWidth(0)
          , nearPlaneHeight(0) {
        screenPosition = GetScreenPosition();
        CalculateNearPlane(nearPlaneWidth, nearPlaneHeight);
    }

    PerspectiveCamera::~PerspectiveCamera() = default;

    Ray PerspectiveCamera::GetRay(uint32_t x, uint32_t y) const {
        const Vector3 screenRight = -direction.Cross({0., 1., 0.}).Normal();
        const Vector3 screenUp = -direction.Cross(screenRight).Normal();

        const Vector3 screenLeft = -screenRight;
        const Vector3 screenDown = -screenUp;

        const Vector3 screenStart = screenLeft * nearPlaneWidth * 0.5
            + screenUp * nearPlaneHeight * 0.5
            + direction * nearPlaneDistance + position;

        const flt screenStepX = nearPlaneWidth / resolutionX;
        const flt screenStepY = nearPlaneHeight / resolutionY;

        // add small jitter to allow SMAA
        flt jitterX, jitterY;
        Algorithms::RandomPointInCircle(jitterX, jitterY);
        constexpr flt jitterStrenth = 0.5f;

        const Vector3 scrrenOffset
            = screenStepX * (static_cast<flt>(x) + jitterX * jitterStrenth) * screenRight
            + screenStepY * (static_cast<flt>(y) + jitterY * jitterStrenth) * screenDown;

        return Ray::FromTwoPoints(position, screenStart + scrrenOffset);
    }

    Vector3 PerspectiveCamera::GetScreenPosition() const {
        return position + direction * nearPlaneDistance;
    }

    void PerspectiveCamera::CalculateNearPlane(flt& nearPlaneWidth, flt& nearPlaneHeight) const {
        flt aspectRatio = static_cast<flt>(resolutionX) / resolutionY;

        nearPlaneWidth = 1.f;
        nearPlaneHeight = nearPlaneWidth * aspectRatio;
    }
}
