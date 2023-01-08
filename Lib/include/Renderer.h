#pragma once

#include <array>
#include "TVector3.h"

using namespace SG;

namespace SG {

    class Renderer {
    private:
        std::array<std::array<bool, 60>, 60> pixels;

    public:
        Renderer();

        void Draw();
        void RayCast(TVector3<double> cameraPosition, TVector3<double> cameraDirection);

    };

} // SG
