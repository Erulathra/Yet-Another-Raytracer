#include "Renderer.h"
#include "iostream"
#include "TLinearMath.h"

namespace SG {
    Renderer::Renderer() {
        for( std::array<bool, 60>& column : pixels) {
            for (bool& pixel: column) {
                pixel = false;
            }
        }
    }

    void Renderer::Draw() {
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

    void Renderer::RayCast(TVector3<double> cameraPosition, TVector3<double> cameraDirection) {
        double pixelSize = 1. / 60.;
        double screenDistance = 1.f;

        TVector3<double> screenPosition = cameraPosition + cameraDirection * screenDistance;

        TVector3<double> worldUp{0., 1., 0.};

        if (cameraDirection.IsNear(TVector3<double>{0, 1, 0}, 0.1)
        || cameraDirection.IsNear(TVector3<double>{0, 1, 0}, 0.1)) {
            worldUp = TVector3<double>(0., 0., 1.);
        }

        TVector3<double> screenLeft = -(screenPosition - cameraPosition).Cross(worldUp).Normal();
        TVector3<double> screenDown = screenPosition.Cross(screenLeft).Normal();

        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                TVector3<double> pixelLocation = screenPosition + ((j - 30) * pixelSize) * screenLeft;
                pixelLocation = pixelLocation + ((i - 30) * pixelSize) * screenDown;

                TLine line = TLine<double>::FromTwoPoints(cameraPosition, pixelLocation);
                pixels[i][j] = TLinearMath<double>::IsRayIntersectAABBUnitBox(line);
            }
        }
    }

} // SG