#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
    YAR::Renderer renderer;

    Vector3 cameraPosition(0.f, 0.f, -5.f);
    Vector3 cameraDirection (0.f, 0.f, 1.f);
    cameraDirection = cameraDirection.Normal();

    renderer.RayCast(cameraPosition, cameraDirection);
    renderer.Draw();
}
