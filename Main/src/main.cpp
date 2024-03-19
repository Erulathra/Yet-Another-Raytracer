#include "Algorithms.h"
#include "Camera.h"
#include "Mat4.h"
#include "Renderable.h"
#include "Renderer.h"
#include "Vector3.h"

void CreateCornerBox(YAR::Renderer& renderer) {
    YAR::Material greenMat{};
    greenMat.color.hex = 0xff00ff00;
    
    YAR::Material blueMat{};
    blueMat.color.hex = 0xff0000ff;
    
    YAR::Material whiteMat{};
    whiteMat.color.hex = 0xffffffff;

    YAM::Mat4 WholeT = YAM::Mat4::Scale(2.f, 2.f, 2.f);

    YAM::Mat4 CoreT = YAM::Mat4::RotationY(YAM::ToRad(180));
    std::shared_ptr<YAR::MeshRenderable> coreRen = std::make_shared<YAR::MeshRenderable>(whiteMat,"res/cornerboxCenter.obj");
    coreRen->Transform(CoreT * WholeT);

    YAM::Mat4 LeftT = YAM::Mat4::Translation(-1.f, 0.f, 0.f) * YAM::Mat4::RotationZ(YAM::ToRad(90));
    std::shared_ptr<YAR::MeshRenderable> leftRen = std::make_shared<YAR::MeshRenderable>(greenMat,"res/plane.obj");
    leftRen->Transform(LeftT * WholeT);
    
    YAM::Mat4 RightT = YAM::Mat4::Translation(1.f, 0.f, 0.f) * YAM::Mat4::RotationZ(YAM::ToRad(-90));
    std::shared_ptr<YAR::MeshRenderable> rightRen = std::make_shared<YAR::MeshRenderable>(blueMat,"res/plane.obj");
    rightRen->Transform(RightT * WholeT);
    
    renderer.AddRenderable(coreRen);
    renderer.AddRenderable(leftRen);
    renderer.AddRenderable(rightRen);
}

int main(int argc, char* argv[]) {
    uint32_t resX = 512, resY = 512;
    // uint32_t resX = 64, resY = 64;
    
    YAR::Renderer renderer{resX, resY, 512, 16, 8};

    YAM::Vector3 cameraPosition(0.f, 0.f, -3.f);
    YAM::Vector3 cameraDirection = YAM::Vector3{0.f} - cameraPosition;
    cameraDirection = cameraDirection.Normal();

    YAR::Material blue{};
    blue.color.hex = 0xff0000ff;
    
    YAR::Material red{};
    red.color.hex = 0xffff0000;
    
    YAR::Material emmisiveWhite{};
    emmisiveWhite.color.hex = 0xff000000;
    emmisiveWhite.emisiveColor.hex = 0xffffffff;
    emmisiveWhite.emmision = 2.f;

    YAM::Sphere sphere {YAM::Vector3{-0.3f, 0.3f, 0.f}, 0.5f};
    std::shared_ptr<YAR::SphereRenderable> sphereOne = std::make_shared<YAR::SphereRenderable>(emmisiveWhite, sphere);
    renderer.AddRenderable(sphereOne);
    
    sphere = {YAM::Vector3{0.5f, -0.5f, 0.f}, 0.2f};
    std::shared_ptr<YAR::SphereRenderable> sphereTwo = std::make_shared<YAR::SphereRenderable>(red, sphere);
    renderer.AddRenderable(sphereTwo);
    
    // YAR::Material material{};
    // material.color.hex = 0xffffffff;
    // std::shared_ptr<YAR::MeshRenderable> renderable = std::make_shared<YAR::MeshRenderable>(material,"res/plumber.obj");
    // YAM::Mat4 transform = YAM::Mat4::Scale(0.25f, 0.25f, 0.25f) * YAM::Mat4::RotationY(YAM::ToRad(180.f)) * YAM::Mat4::Translation(0.f, 0.f, -0.3f);
    // renderable->Transform(transform);
    // renderer.AddRenderable(renderable);

    CreateCornerBox(renderer);
    
    // std::unique_ptr<YAR::Camera> camera = std::make_unique<YAR::OrthoCamera>(
    //     resX, resY, cameraPosition, cameraDirection, 3.f, 3.f);
    std::shared_ptr<YAR::Camera> camera = std::make_shared<YAR::PerspectiveCamera>(
        resX, resY, cameraPosition, cameraDirection, 1.f );

    renderer.Render(camera);
    renderer.Save("output.tga");
}
