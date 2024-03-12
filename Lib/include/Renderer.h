#pragma once

#include <array>
#include "Vector3.h"

using namespace SG;

namespace SG {

    class Renderer {
    private:
        std::array<std::array<bool, 60>, 60> pixels{};

    public:
        Renderer();

        void Draw() const;
        void RayCast(const Vector3& cameraPosition, const Vector3& cameraDirection);

    };

} // SG
