#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "Vector3.h"

namespace YAR{
    struct RenderHitInfo;
}

namespace YAM{
    struct Ray;
}

namespace YAR{
    struct RenderBounds {
        uint32_t minX;
        uint32_t minY;

        uint32_t maxX;
        uint32_t maxY;

        RenderBounds();
    };

    class Renderable;
    class Buffer;
    class Camera;

    class Renderer {
    private:
        std::unique_ptr<Buffer> colorBuffer;
        mutable std::mutex colorBufferMutex;
        mutable std::mutex fileIOMutex;

        std::vector<std::shared_ptr<Renderable>> renderables;

        uint32_t samplesPerPixel;
        uint32_t maxBounces;
        uint32_t tilesPerRow;

        std::shared_ptr<Camera> camera;

    public:
        Renderer(uint32_t sizeX, uint32_t sizeY, uint32_t samplesPerPixel, uint32_t maxBounces, uint32_t tilesPerRow);
        ~Renderer();

        void AddRenderable(const std::shared_ptr<Renderable>& renderable);

        void Render(const std::shared_ptr<YAR::Camera> camera);
        void Save(const std::string& path) const;

        uint32_t GetSamplesPerPixel() const { return samplesPerPixel; }
        uint32_t GetMaxBounces() const { return maxBounces; }
        uint32_t GetTilesPerRow() const { return tilesPerRow; }

        friend class RenderWorker;
    };
} // SG
