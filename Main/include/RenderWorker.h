#pragma once
#include <memory>

#include "Algorithms.h"
#include "Renderer.h"
#include "Vector3.h"

namespace YAR{
    class Camera;

    class RenderWorker {
        std::shared_ptr<Camera> camera;
        RenderBounds renderBounds;

        YAM::Random random;

        Renderer& owner;
    public:
        RenderWorker(Renderer& owner, const std::shared_ptr<Camera>& camera, const RenderBounds& renderBounds);

        void StartRender() const;
        YAM::Vector3 SamplePixel(const Camera* camera, uint32_t y, uint32_t x) const;
        bool CalculateRayCollision(const YAM::Ray& ray, RenderHitInfo& outHit) const;
    };
} // YAR
