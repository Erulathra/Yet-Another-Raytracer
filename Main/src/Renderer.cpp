#include "Renderer.h"

#include "Buffer.h"
#include "Camera.h"
#include "LinearMath.h"
#include "Mesh.h"
#include "TGAWriter.h"

using namespace YAM;

namespace YAR {
    Renderer::Renderer(uint32_t sizeX, uint32_t sizeY) {
        colorBuffer = std::make_unique<YAR::Buffer>(sizeX, sizeY);
    }

    Renderer::~Renderer() = default;

    void Renderer::Render(const YAR::Camera* camera) const {
        Mesh mesh{"res/monke.obj"};
        HitInfo hitInfo;

        colorBuffer->FillColor(0xff000000);
        colorBuffer->FillDepth(std::numeric_limits<float>::min());
        
        for (int i = 0; i < colorBuffer->GetSizeX(); ++i) {
            for (int j = 0; j < colorBuffer->GetSizeY(); ++j) {
                Ray ray = camera->GetRay(j, i);

                for (Triangle triangle : mesh.GetTriangles()) {
                    if (LinearMath::FindIntersection(ray, triangle, hitInfo)) {
                        if (hitInfo.distance > colorBuffer->GetDepth(j, i)) {
                            colorBuffer->SetPix(j, i, hitInfo.color);
                            colorBuffer->SetDepth(j, i, hitInfo.distance);
                        }
                    }
                }
            }
        }
    }

    void Renderer::Save(const std::string& path) const {
        TGAWriter::Write(path, colorBuffer->GetData(), colorBuffer->GetSizeX(), colorBuffer->GetSizeY());
    }
} // SG