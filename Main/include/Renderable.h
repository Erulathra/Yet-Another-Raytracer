#pragma once
#include "LinearMath.h"
#include "Mesh.h"

namespace YAR{
    struct Material {
        YAM::Color color;
        YAM::Color emisiveColor;
        float emmision;
        float specular;

        float transparency;
        float refractiveIndex;

        Material();
    };

    struct RenderHitInfo : public YAM::HitInfo {
        const Material* material;

        RenderHitInfo();

        RenderHitInfo& operator=(const RenderHitInfo& hitInfo) {
            hitPoint = hitInfo.hitPoint;
            normal = hitInfo.normal;
            distance = hitInfo.distance;
            material = hitInfo.material;
            
            return *this;
        }
    };

    class Renderable {
    private:
        Material material;

    protected:
        Material& GetMaterial() { return material; }

    public:
        explicit Renderable(const Material& material);
        virtual ~Renderable() = 0;

        virtual bool Trace(const YAM::Ray& ray, RenderHitInfo& hitInfo) = 0;
    };

    class SphereRenderable : public Renderable {
    private:
        YAM::Sphere sphere;

    public:
        SphereRenderable(const Material& material, const YAM::Sphere& sphere);
        ~SphereRenderable() override;

        bool Trace(const YAM::Ray& ray, RenderHitInfo& hitInfo) override;
    };

    class MeshRenderable : public Renderable {
    private:
        Mesh mesh;

    public:
        MeshRenderable(const Material& material, const std::string& objPath);
        ~MeshRenderable() override;

        bool Trace(const YAM::Ray& ray, RenderHitInfo& outHit) override;

        void Transform(const YAM::Mat4& mat4);
    };
}
