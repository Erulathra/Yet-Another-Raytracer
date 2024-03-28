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
                const Material* material = hitInfo.material;
                
                // cosine weighted ray districution
                const YAM::Vector3 diffuse = (hitInfo.normal + random.RandomDirection()).Normal();
                const YAM::Vector3 specular = Reflect(ray.direction, hitInfo.normal);

                const float dirDotNormal = YAM::Vector3::Dot(ray.direction, hitInfo.normal);
                float refractiveRatio;
                float normalFactor;
                
                if (dirDotNormal < 0.) {
                    refractiveRatio = 1.f / material->refractiveIndex;
                    normalFactor = 1.f;
                }
                else {
                    refractiveRatio = material->refractiveIndex;
                    normalFactor = -1.f;
                }

                const YAM::Vector3 refraction = Refract(ray.direction, normalFactor * hitInfo.normal, refractiveRatio);
                
                ray.direction = YAM::Vector3::Lerp(diffuse, specular, hitInfo.material->specular);

                float fresnell = 1.f - YAM::Fresnell(ray.direction, hitInfo.normal);
                fresnell = std::pow(fresnell, 0.6f);
                fresnell = 1.f;
                
                ray.direction = YAM::Vector3::Lerp(ray.direction, refraction, material->transparency * fresnell);
                    
                const YAM::Vector3 materialColor = material->color.ToVector();
                const YAM::Vector3 emissionColor = material->emisiveColor.ToVector();
                const YAM::Vector3 emitedLight = emissionColor * material->emmision;
                float lightStrenght = YAM::Vector3::Dot(hitInfo.normal, ray.direction);
                lightStrenght = YAM::Lerp(lightStrenght, 1.f, material->transparency * fresnell);
                
                finalColor += emitedLight.Mul(rayColor);
                rayColor = rayColor.Mul(materialColor) * lightStrenght;
                
                ray.point = hitInfo.hitPoint;
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
