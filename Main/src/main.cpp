#include "Algorithms.h"
#include "Camera.h"
#include "Mat4.h"
#include "Renderable.h"
#include "Renderer.h"
#include "Vector3.h"

void ExerciseOne();

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
    YAM::Algorithms::SetRandomSeed(time(nullptr));
    
    uint32_t resX = 512, resY = 512;
    // uint32_t resX = 64, resY = 64;
    
    YAR::Renderer renderer{resX, resY};

    YAM::Vector3 cameraPosition(0.f, 0.f, -3.f);
    YAM::Vector3 cameraDirection = YAM::Vector3{0.f} - cameraPosition;
    cameraDirection = cameraDirection.Normal();

    YAR::Material blue{};
    blue.color.hex = 0xff0000ff;

    YAM::Sphere sphere {YAM::Vector3{-0.4f, -0.5f, 0.f}, 0.5f};
    std::shared_ptr<YAR::SphereRenderable> sphereOne = std::make_shared<YAR::SphereRenderable>(blue, sphere);
    renderer.AddRenderable(sphereOne);
    
    YAR::Material red{};
    red.color.hex = 0xffff0000;
    
    sphere = {YAM::Vector3{1.1f, 0.8f, 0.f}, 0.2f};
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
    std::unique_ptr<YAR::Camera> camera = std::make_unique<YAR::PerspectiveCamera>(
        resX, resY, cameraPosition, cameraDirection, 1.f );

    renderer.Render(camera.get());
    renderer.Save("output.tga");

    ExerciseOne();
}

void ExerciseOne() {
    spdlog::info("====================== Ex. 1 ========================");
    
    YAM::Vector3 sampleOne = {0.f, 3.f, 0.f};
    YAM::Vector3 sampleTwo = {5.f, 5.f, 0.f};

    spdlog::info("{} + {} = {}", sampleOne.str(), sampleTwo.str(), (sampleOne + sampleTwo).str());
    spdlog::info("Angle from {} to {} is {}", sampleTwo.str(), sampleOne.str(), sampleTwo.Angle(sampleOne));

    
    sampleOne = {4.f, 5.f, 1.f};
    sampleTwo = {4.f, 1.f, 3.f};
    YAM::Vector3 normalVec = sampleOne.Cross(sampleTwo);
    spdlog::info("{} x {} = {}", sampleOne.str(), sampleTwo.str(), normalVec.str());
    spdlog::info("Normal: {}", normalVec.Normal().str());

    YAM::Sphere S {YAM::Vector3{0.f}, 10};
    YAM::Vector3 RayPoint{0, 0, -20};
    YAM::Ray R1 {-RayPoint.Normal(), RayPoint};
    YAM::Ray R2 {YAM::Vector3{0.f, 1.f, 0.f}, RayPoint};

    YAM::HitInfo hitInfo;
    if (YAM::LinearMath::FindIntersection(R1, S, hitInfo)) {
        spdlog::info("R1 and S: {}", hitInfo.hitPoint.str());
    }
    else {
        spdlog::info("R1 and S: no intersection.");
    }
    
    if (YAM::LinearMath::FindIntersection(R2, S, hitInfo)) {
        spdlog::info("R2 and S: {}", hitInfo.hitPoint.str());
    }
    else {
        spdlog::info("R2 and S: no intersection.");
    }
    
    YAM::Ray R3 {YAM::Vector3{0.f, 0.f, 1.f}, YAM::Vector3{0.f, 10.f, -20.f}};
    if (YAM::LinearMath::FindIntersection(R3, S, hitInfo)) {
        spdlog::info("R3 and S: {}", hitInfo.hitPoint.str());
    }

    YAM::Plane P;
    P.point = YAM::Vector3{0.f};
    P.normalVector = YAM::Vector3 {0.f, 1.f, 1.f};
    P.normalVector = P.normalVector.Normal();


    YAM::Vector3 result;
    if (YAM::LinearMath::FindIntersection(R2, P, result)) {
        spdlog::info("R3 and P: {}", result.str());
    }

    YAM::Triangle triangle{{0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}};
    YAM::Ray R4 = YAM::Ray::FromTwoPoints({-1, 0.5, 0}, {1, 0.5, 0});

    if (YAM::LinearMath::FindIntersection(R4, triangle, hitInfo)) {
        spdlog::info("R4 and Triangle: {}", hitInfo.hitPoint.str());
    }
    
    YAM::Ray R5 = YAM::Ray::FromTwoPoints({2, -1, 0}, {2, 2, 0});
    spdlog::info("R5 and Triangle: {}", YAM::LinearMath::FindIntersection(R5, triangle, hitInfo));
    
    YAM::Ray R6 = YAM::Ray::FromTwoPoints( {0, 0, 1}, {0, 0, -1});
    spdlog::info("R6 and Triangle: {}", YAM::LinearMath::FindIntersection(R6, triangle, hitInfo));

    
    YAM::Sphere S2 {YAM::Vector3{0.f, 10.f, 0.f}, 10};
    YAM::Ray R7 = YAM::Ray::FromTwoPoints({0.f, -10.f, 0.f}, YAM::Vector3{0.f});

    if (YAM::LinearMath::FindIntersection(R7, S2, hitInfo)) {
        spdlog::info("R7 and S2: {}", hitInfo.hitPoint.str());
    }
    else {
        spdlog::info("R7 and S2: no intersection.");
    }
    
    YAM::Plane P2 {YAM::Vector3{0.f, 1.f, 0.f}, YAM::Vector3{0.f}};
    YAM::Ray R8 = YAM::Ray::FromTwoPoints({0.f, -10.f, 0.f}, YAM::Vector3{0.f});

    YAM::Vector3 vector3;
    if (YAM::LinearMath::FindIntersection(R8, P2, vector3)) {
        spdlog::info("P2 and R8: {}", vector3.str());
    }
    else {
        spdlog::info("P2 and R8: no intersection.");
    }
}
