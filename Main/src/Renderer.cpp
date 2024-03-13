#include "Renderer.h"

#include "Buffer.h"
#include "Camera.h"
#include "LinearMath.h"
#include "TGAWriter.h"

using namespace YAM;

namespace YAR {
    Renderer::Renderer(uint32_t sizeX, uint32_t sizeY) {
        colorBuffer = std::make_unique<Buffer>(sizeX, sizeY);
    }

    Renderer::~Renderer() = default;

    void Renderer::Render(const Camera* camera) const {
        for (int i = 0; i < colorBuffer->GetSizeX(); ++i) {
            for (int j = 0; j < colorBuffer->GetSizeY(); ++j) {
                Ray ray = camera->GetRay(i, j);

                Sphere sphere {Vector3{0.f}, 1.f};
                std::vector<Vector3> result;
                const bool WasIntesection = LinearMath::FindIntersection(ray, sphere, result);

                colorBuffer->SetPix(i, j, WasIntesection ? 0xffffffff : 0xff000000);
            }
        }
    }

    void Renderer::Save(const std::string& path) const {
        TGAWriter::Write(path, colorBuffer->GetData(), colorBuffer->GetSizeX(), colorBuffer->GetSizeY());
    }
} // SG