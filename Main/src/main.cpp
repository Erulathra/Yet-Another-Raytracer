#include "Camera.h"
#include "Renderable.h"
#include "Renderer.h"
#include "Vector3.h"

int main(int argc, char* argv[]) {
    uint32_t resX = 256, resY = 256;
    
    YAR::Renderer renderer{resX, resY};

    YAM::Vector3 cameraPosition(0.f, 0.f, 10.f);
    YAM::Vector3 cameraDirection = YAM::Vector3{0.f} - cameraPosition;
    cameraDirection = cameraDirection.Normal();

    cameraPosition += {0.f, 0.f, 0.f};

    YAR::Material material{};
    material.color.hex = 0xffffffff;
    std::shared_ptr<YAR::MeshRenderable> renderable = std::make_shared<YAR::MeshRenderable>(material,"res/plumber.obj");
    renderer.AddRenderable(renderable);
    
    YAR::Material material2{};
    material2.color.hex = 0xffff0000;

    YAM::Sphere sphere {{0.f, 0.f, -10.f}, 3.f};
    std::shared_ptr<YAR::SphereRenderable> sphereRen = std::make_shared<YAR::SphereRenderable>(material2, sphere);
    renderer.AddRenderable(sphereRen);
    
    // std::unique_ptr<YAR::Camera> camera = std::make_unique<YAR::OrthoCamera>(
    //     resX, resY, cameraPosition, cameraDirection, 3.f, 3.f);
    std::unique_ptr<YAR::Camera> camera = std::make_unique<YAR::PerspectiveCamera>(
        resX, resY, cameraPosition, cameraDirection, 30.f, 0.01);

    renderer.Render(camera.get());
    renderer.Save("output.tga");
}
