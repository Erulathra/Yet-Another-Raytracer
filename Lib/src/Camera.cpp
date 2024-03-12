#include "Camera.h"

namespace YAR {
    Ray OrthoCamera::GetRay(uint32_t X, uint32_t Y, uint32_t ResX, uint32_t ResY) {
        const flt stepX = static_cast<flt>(orthoSizeX) / ResX;
        const flt stepY = static_cast<flt>(orthoSizeY) / ResY;

        const Vector3 screenRight = -direction.Cross({0., 1., 0.}).Normal();
        const Vector3 screenUp = direction.Cross(screenRight).Normal();

        const Vector3 screenLeft = -screenRight;
        const Vector3 screenDown = -screenUp;

        Vector3 screenStart = position + (screenLeft * (orthoSizeX * 0.5f))
                                       + (screenUp * (orthoSizeY * 0.5f));

        Vector3 screenOffset = (stepX * X) * screenRight
                             + (stepY * Y) * screenDown;

        return {screenStart + screenOffset, position};
    }
}
