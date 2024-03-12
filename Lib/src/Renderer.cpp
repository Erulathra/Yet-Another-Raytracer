#include "Renderer.h"
#include "iostream"
#include "LinearMath.h"

namespace SG {
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
        const double pixelSize = 1. / 60.;
        const double screenDistance = 1.f;

        const Vector3 screenPosition = cameraPosition + cameraDirection * screenDistance;

        Vector3 worldUp{0., 1., 0.};

        if (cameraDirection.IsNear(Vector3{0, 1, 0}, 0.1)
        || cameraDirection.IsNear(Vector3{0, 1, 0}, 0.1)) {
            worldUp = Vector3(0., 0., 1.);
        }

        const Vector3 screenLeft = -(screenPosition - cameraPosition).Cross(worldUp).Normal();
        const Vector3 screenDown = screenPosition.Cross(screenLeft).Normal();

        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                Vector3 pixelLocation = screenPosition + ((j - 30) * pixelSize) * screenLeft;
                pixelLocation = pixelLocation + ((i - 30) * pixelSize) * screenDown;

                Ray ray = Ray::FromTwoPoints(cameraPosition, pixelLocation);
                Sphere sphere {{0.f}, 1.f};
                std::vector<Vector3> result;
                pixels[i][j] = LinearMath::FindIntersection(ray, sphere, result);
            }
        }
    }

} // SG