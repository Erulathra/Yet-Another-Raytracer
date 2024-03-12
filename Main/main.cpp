#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
    YAR::Renderer renderer;

    double yaw = 30.;
    double pitch = 30.;
    double radius = 5.;

    std::cout << "Pitch: " << pitch << " Yaw: " << yaw << " Radius: " << radius << "         " << std::endl;

    if (pitch >= 360.)
        pitch -= 360.;
    else if (pitch < 0.)
        pitch += 360.;

    Vector3 cameraPosition(0.f);

    const double pitchRadians = pitch * M_PI / 180.;
    const double yawRadians = yaw * M_PI / 180.;
    cameraPosition.x = radius * std::cos(pitchRadians) * std::cos(yawRadians);
    cameraPosition.y = radius * std::sin(pitchRadians) * std::cos(yawRadians);
    cameraPosition.z = radius * std::sin(yawRadians);

    Vector3 cameraDirection = (-cameraPosition).Normal();

    renderer.RayCast(cameraPosition, cameraDirection);
    renderer.Draw();
}
