#include "Renderer.h"

#include "Buffer.h"
#include "Camera.h"
#include "LinearMath.h"
#include "Mesh.h"
#include "Renderable.h"
#include "TGAWriter.h"
#include "spdlog/spdlog.h"

using namespace YAM;

namespace YAR {
    Renderer::Renderer(uint32_t sizeX, uint32_t sizeY) {
        colorBuffer = std::make_unique<YAR::Buffer>(sizeX, sizeY);
    }

    Renderer::~Renderer() = default;
    void Renderer::AddRenderable(const std::shared_ptr<Renderable>& renderable) {
        renderables.push_back(renderable);
    }

    void Renderer::Render(const YAR::Camera* camera) const {
        colorBuffer->FillColor(0xff000000);
        
        for (int i = 0; i < colorBuffer->GetSizeX(); ++i) {
            for (int j = 0; j < colorBuffer->GetSizeY(); ++j) {
                Ray ray = camera->GetRay(j, i);

                RenderHitInfo closestHit;
                closestHit.distance = std::numeric_limits<float>::max();
                
                bool wasIntersection = false;
                
                for (const std::shared_ptr<Renderable>& renderable : renderables) {
                    if (RenderHitInfo hitInfo; renderable->Trace(ray, hitInfo)) {
                        if (hitInfo.distance < closestHit.distance) {
                            closestHit = hitInfo;
                            wasIntersection = true;
                        }
                    }
                }

                if (wasIntersection) {
                    const Vector3 lightDir =  {-1.f, 1.f, 1.f};

                    const Vector3 objColor = closestHit.material->color.ToVector();
                    const Color color = Color::FromVector(
                        objColor * Vector3::Dot(closestHit.normal, lightDir.Normal()));

                    colorBuffer->SetPix(j, i, color.hex);
                }
            }
        }
    }

    void Renderer::Save(const std::string& path) const {
        TGAWriter::Write(path, colorBuffer->GetData(), colorBuffer->GetSizeX(), colorBuffer->GetSizeY());
    }
} // SG