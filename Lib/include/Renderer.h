#pragma once

#include <array>
#include "Math/Vector3.h"

using namespace YAR;

namespace YAR {

    class Renderer {
    private:
        std::array<std::array<bool, 60>, 60> pixels{};

    public:
        Renderer();

        void Draw() const;
        void RayCast(const Vector3& cameraPosition, const Vector3& cameraDirection);

    };

} // SG
