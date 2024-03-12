#include "Renderer.h"

#include "Camera.h"
#include "iostream"
#include "Math/LinearMath.h"

namespace YAR {
    Renderer::Renderer() {
        for( std::array<bool, 60>& column : pixels) {
            for (bool& pixel: column) {
                pixel = false;
            }
        }
    }

    void Renderer::Draw() const {
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                if (pixels[i][j])
                {
                    std::cout << "0";
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }

    void Renderer::RayCast(const Vector3& cameraPosition, const Vector3& cameraDirection) {
        OrthoCamera camera{cameraPosition, cameraDirection, 5.f, 5.f};

        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                Ray ray = camera.GetRay(i, j, 60, 60);

                Sphere sphere {{0.f}, 1.f};
                std::vector<Vector3> result;
                pixels[i][j] = LinearMath::FindIntersection(ray, sphere, result);
            }
        }
    }

} // SG