#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "../../cmake-build-debug/_deps/spdlog-src/include/spdlog/spdlog.h"

int main(int argc, char* argv[]) {
    YAM::Renderer renderer;

    YAM::Vector3 cameraPosition(0.f, 0.f, -5.f);
    YAM::Vector3 cameraDirection (0.f, 0.f, 1.f);
    cameraDirection = cameraDirection.Normal();

    renderer.RayCast(cameraPosition, cameraDirection);
    renderer.Draw();
}
