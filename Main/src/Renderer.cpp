#include "Renderer.h"

#include "Algorithms.h"
#include "Buffer.h"
#include "Camera.h"
#include "LinearMath.h"
#include "Renderable.h"
#include "RenderWorker.h"
#include "TGAWriter.h"
#include "spdlog/spdlog.h"

using namespace YAM;

namespace YAR{
    Renderer::Renderer(uint32_t sizeX, uint32_t sizeY,
                       uint32_t samplesPerPixel, uint32_t maxBounces, uint32_t tilesPerRow)
        : colorBufferMutex()
          , samplesPerPixel(samplesPerPixel)
          , maxBounces(maxBounces)
          , tilesPerRow(tilesPerRow) {
        colorBuffer = std::make_unique<YAR::Buffer>(sizeX, sizeY);
    }

    Renderer::~Renderer() = default;

    void Renderer::AddRenderable(const std::shared_ptr<Renderable>& renderable) {
        renderables.push_back(renderable);
    }

    void Renderer::Render(const std::shared_ptr<YAR::Camera> camera) {
        colorBuffer->FillColor(0xff000000);

        const uint32_t tilesNum = tilesPerRow * tilesPerRow;
        std::vector<uint32_t> numbers;
        for (int i = 0; i < tilesNum; ++i) {
            numbers.push_back(i);
        }

        std::atomic<uint32_t> finishedTiles = 0;
        
#pragma omp parallel for
        for (int tileID = 0; tileID < tilesNum; ++tileID) {
            const uint32_t tileY = tileID / tilesPerRow;
            const uint32_t tileX = tileID - tileY * tilesPerRow;

            RenderBounds renderBounds{};
            renderBounds.minX = tileX * colorBuffer->GetSizeX() / tilesPerRow;
            renderBounds.minY = tileY * colorBuffer->GetSizeY() / tilesPerRow;
            renderBounds.maxX = renderBounds.minX + colorBuffer->GetSizeX() / tilesPerRow;
            renderBounds.maxY = renderBounds.minY + colorBuffer->GetSizeY() / tilesPerRow;

            RenderWorker renderWorker(*this, camera, renderBounds);
            renderWorker.StartRender();
            
            ++finishedTiles;
            spdlog::info("Progress: {}%", 100.f * static_cast<float>(finishedTiles) / tilesNum);
        }
    }

    void Renderer::Save(const std::string& path) const {
        std::scoped_lock lock{fileIOMutex};
        TGAWriter::Write(path, colorBuffer->GetData(), colorBuffer->GetSizeX(), colorBuffer->GetSizeY());
    }

    RenderBounds::RenderBounds()
        : minX(0)
          , minY(0)
          , maxX(0)
          , maxY(0) {}
} // SG
