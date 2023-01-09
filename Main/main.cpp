#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "cpp-terminal/base.hpp"
#include "spdlog/spdlog.h"
#include "cpp-terminal/input.hpp"

int main(int argc, char* argv[]) {
    SG::Renderer renderer;

    double pitch = 0.;
    double yaw = 0.;
    double radius = 5.;

    if (!Term::stdin_connected()) {
        SPDLOG_ERROR("The terminal is not attached to a TTY and therefore can't catch user input. Exiting...");
        return 1;
    }

    Term::Terminal term(true, true, true, false);
    std::cout << Term::cursor_move(1, 1);
    std::cout << "WASD to orbit" << std::endl;
    std::cout << "QE to move" << std::endl;
    std::cout << "ctrl-c to quit" << std::endl;
    bool endlessLoop = true;

    while (endlessLoop) {
        std::cout << Term::cursor_move(4, 1);
        std::cout << "Pitch: " << pitch << " Yaw: " << yaw << " Radius: " << radius << "         " << std::endl;
        Term::Key key{static_cast<Term::Key>(Term::read_key())};

        if (key == Term::CTRL_C)
            endlessLoop = false;

        if (key == 'w')
            pitch += 10.;
        else if (key == 's')
            pitch -= 10.;
        else if (key == 'd')
            yaw += 10.;
        else if (key == 'a')
            yaw -= 10.;
        else if (key == 'e')
            radius += 0.5;
        else if (key == 'q')
            radius -= 0.5;

        TVector3<double> cameraPosition(0.f);

        double yawRadians = yaw * M_PI / 180.;
        double pitchRadians = pitch * M_PI / 180.;
        cameraPosition.x = radius * std::cos(pitchRadians) * std::cos(yawRadians);
        cameraPosition.y = radius * std::sin(pitchRadians);
        cameraPosition.z = radius * std::cos(pitchRadians) * std::sin(-yawRadians);

        TVector3<double> cameraDirection = (-cameraPosition).Normal();

        renderer.RayCast(cameraPosition, cameraDirection);
        renderer.Draw();
    }
}
