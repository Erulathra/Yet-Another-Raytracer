#include "RenderWorker.h"

#include "Buffer.h"
#include "Camera.h"
#include "Renderable.h"

namespace YAR{
    RenderWorker::RenderWorker(Renderer& owner, const std::shared_ptr<Camera>& camera, const RenderBounds& renderBounds)
    : owner(owner), camera(camera), renderBounds(renderBounds) {
        random.SetRandomSeed(renderBounds.minX + renderBounds.minY * owner.colorBuffer->GetSizeX() + 195487);
    }

    void RenderWorker::StartRender() const {
        uint32_t samplesPerPixel = owner.GetSamplesPerPixel();
        
        std::vector<YAM::Vector3> samples;
        samples.resize(samplesPerPixel);

        for (uint32_t i = renderBounds.minY; i < renderBounds.maxY; ++i) {
            for (uint32_t j = renderBounds.minX; j < renderBounds.maxX; ++j) {
                for (YAM::Vector3& sample : samples) {
                    sample = YAM::Vector3{0.f};
                }

                for (uint32_t sampleID = 0; sampleID < samplesPerPixel; ++sampleID) {
                    samples[sampleID] = SamplePixel(camera.get(), i, j);
                }

                YAM::Vector3 finalColor = YAM::Vector3{0};
                for (uint32_t sampleID = 0; sampleID < samplesPerPixel; ++sampleID) {
                    finalColor += samples[sampleID];
                }
                
                {
                    std::scoped_lock lock{owner.colorBufferMutex};
                    owner.colorBuffer->SetPix(j, i, YAM::Color::FromVector(finalColor / static_cast<YAM::flt>(samplesPerPixel)).hex);
                }
            }
        }
    }

    YAM::Vector3 RenderWorker::SamplePixel(const Camera* camera, uint32_t y, uint32_t x) const {
        YAM::Ray ray = camera->GetRay(x, y, random);

        YAM::Vector3 finalColor {0.f};
        YAM::Vector3 rayColor {1.f};

        uint32_t maxBounces = owner.GetMaxBounces();
        
        for (uint32_t bounceId = 0; bounceId <= maxBounces; ++bounceId) {
            RenderHitInfo hitInfo;

            if (CalculateRayCollision(ray, hitInfo)) {
                ray.point = hitInfo.hitPoint;
                ray.direction = random.RandomHemisphereDirection(hitInfo.normal);

                const Material* material = hitInfo.material;
                
                const YAM::Vector3 materialColor = material->color.ToVector();
                const YAM::Vector3 emissionColor = material->emisiveColor.ToVector();
                
                const YAM::Vector3 emitedLight = emissionColor * material->emmision;
                finalColor += emitedLight.Mul(rayColor);
                rayColor = rayColor.Mul(materialColor);
            }
            else {
                break;
            }
        }

        return finalColor;
    }

    bool RenderWorker::CalculateRayCollision(const YAM::Ray& ray, RenderHitInfo& outHit) const {
        outHit.distance = std::numeric_limits<YAM::flt>::max();

        bool wasIntersection = false;
        for (const std::shared_ptr<Renderable>& renderable : owner.renderables) {
            RenderHitInfo hit;
            
            if (renderable->Trace(ray, hit) && hit.distance < outHit.distance) {
                outHit = hit;
                wasIntersection = true;
            }
        }

        return wasIntersection;
    }
} // YAR
