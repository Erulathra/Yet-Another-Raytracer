#include "Renderer.h"

#include "Buffer.h"
#include "Camera.h"
#include "LinearMath.h"
#include "Mesh.h"
#include "Renderable.h"
#include "TGAWriter.h"
#include "spdlog/spdlog.h"

using namespace YAM;

namespace YAR{
    Renderer::Renderer(uint32_t sizeX, uint32_t sizeY)
        : colorBufferMutex()
          , samplesPerPixel(4)
          , tilesPerRow(4) {
        colorBuffer = std::make_unique<YAR::Buffer>(sizeX, sizeY);
    }

    Renderer::~Renderer() = default;

    void Renderer::AddRenderable(const std::shared_ptr<Renderable>& renderable) {
        renderables.push_back(renderable);
    }

    void Renderer::Render(const YAR::Camera* camera) const {
        colorBuffer->FillColor(0xff000000);

        const uint32_t tilesNum = tilesPerRow * tilesPerRow;
        std::vector<uint32_t> numbers;
        for (int i = 0; i < tilesNum; ++i) {
            numbers.push_back(i);
        }

#pragma omp parallel for
        for (int tileID = 0; tileID < tilesNum; ++tileID) {
            uint32_t tileY = tileID / tilesPerRow;
            uint32_t tileX = tileID - tileY * tilesPerRow;

            RenderBounds renderBounds{};
            renderBounds.minX = tileX * colorBuffer->GetSizeX() / tilesPerRow;
            renderBounds.minY = tileY * colorBuffer->GetSizeX() / tilesPerRow;
            renderBounds.maxX = renderBounds.minX + colorBuffer->GetSizeX() / 4;
            renderBounds.maxY = renderBounds.minY + colorBuffer->GetSizeY() / 4;

            spdlog::info("Rendering: ({}, {}) to ({}, {})", renderBounds.minX, renderBounds.minY, renderBounds.maxX, renderBounds.maxY);
            RenderWorker(camera, renderBounds);
            
        }
    }

    void Renderer::Save(const std::string& path) const {
        TGAWriter::Write(path, colorBuffer->GetData(), colorBuffer->GetSizeX(), colorBuffer->GetSizeY());
    }

    void Renderer::RenderWorker(const Camera* camera, const RenderBounds& renderBounds) const {
        for (uint32_t i = renderBounds.minY; i < renderBounds.maxY; ++i) {
            for (uint32_t j = renderBounds.minX; j < renderBounds.maxX; ++j) {
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
                    const Vector3 lightDir = {-1.f, 1.f, 1.f};

                    const Vector3 objColor = closestHit.material->color.ToVector();
                    const Color color = Color::FromVector(
                        objColor * Vector3::Dot(closestHit.normal, lightDir.Normal()));

                    {
                        std::scoped_lock lock{colorBufferMutex};
                        colorBuffer->SetPix(j, i, color.hex);
                    }
                }
            }
        }
    }

    RenderBounds::RenderBounds()
        : minX(0)
          , minY(0)
          , maxX(0)
          , maxY(0) {}
} // SG
