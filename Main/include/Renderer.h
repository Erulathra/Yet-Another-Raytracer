#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "Vector3.h"

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

        std::vector<std::shared_ptr<Renderable>> renderables;

        uint32_t samplesPerPixel;
        bool bVariableSamplesPerPixel;
        
        uint32_t tilesPerRow;

        std::shared_ptr<Camera> camera;

    public:
        Renderer(uint32_t sizeX, uint32_t sizeY);
        ~Renderer();

        void AddRenderable(const std::shared_ptr<Renderable>& renderable);

        void Render(const Camera* camera) const;
        void Save(const std::string& path) const;
        YAM::Vector3 SamplePixel(const Camera* camera, uint32_t y, uint32_t x) const;

    private:
        void RenderWorker(const Camera* camera, const RenderBounds& renderBounds) const;
    };
} // SG
