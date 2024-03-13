#include "Camera.h"
#include "Renderer.h"
#include "Vector3.h"

int main(int argc, char* argv[]) {
    YAR::Renderer renderer{256, 256};

    YAM::Vector3 cameraPosition(0.f, 0.f, -5.f);
    YAM::Vector3 cameraDirection (0.f, 0.f, 1.f);
    cameraDirection = cameraDirection.Normal();

    std::unique_ptr<YAR::Camera> camera = std::make_unique<YAR::OrthoCamera>(
        256, 256, cameraPosition, cameraDirection, 5.f, 5.f);

    renderer.Render(camera.get());
    renderer.Save("output.tga");
}
