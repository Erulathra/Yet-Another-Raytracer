#include "Renderer.h"
#include <cmath>
#include <iostream>

int main(int argc, char *argv[]) {
    SG::Renderer renderer;

    double pitch = 0.;
    double yaw = 0.;
    double radius = 5.;

    while (true) {
        std::cout << "Pitch: ";
        std::cin >> pitch;
        std::cout << "yaw: ";
        std::cin >> yaw;
        std::cout << "distance: ";
        std::cin >> radius;

        pitch *= M_PI / 180.;
        yaw *= M_PI / 180.;

        TVector3<double> origin(0.f);
        TVector3<double> cameraPosition(0.f);
        cameraPosition.x = origin.x + radius * std::sin(pitch) * std::cos(yaw);
        cameraPosition.y = origin.z + radius * std::sin(pitch) * std::sin(yaw);
        cameraPosition.z = origin.y + radius * std::cos(pitch);

        TVector3<double> cameraDirection = (-cameraPosition).Normal();

        renderer.RayCast(cameraPosition, cameraDirection);
        renderer.Draw();
    }
}
