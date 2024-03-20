#include "Renderable.h"

#include "spdlog/spdlog.h"

using namespace YAR;

Material::Material()
    : color({0xff000000})
      , emisiveColor({0xff000000})
      , emmision(0)
      , specular(0) {}

RenderHitInfo::RenderHitInfo()
    : material() {}

Renderable::Renderable(const Material& material)
    : material(material) {}

Renderable::~Renderable() = default;

SphereRenderable::SphereRenderable(const Material& material, const YAM::Sphere& sphere)
    : Renderable(material)
      , sphere(sphere) {}

SphereRenderable::~SphereRenderable() = default;

bool SphereRenderable::Trace(const YAM::Ray& ray, RenderHitInfo& hitInfo) {
    bool intersects = YAM::LinearMath::FindIntersection(ray, sphere, hitInfo);

    if (intersects) {
        hitInfo.material = &GetMaterial();
    }

    return intersects;
}

MeshRenderable::MeshRenderable(const Material& material, const std::string& objPath)
    : Renderable(material)
      , mesh(objPath) {}

MeshRenderable::~MeshRenderable() = default;

bool MeshRenderable::Trace(const YAM::Ray& ray, RenderHitInfo& outHit) {
    if (!YAM::LinearMath::FindIntersection(ray, mesh.GetBoudingBox())) {
        return false;
    }

    outHit.distance = std::numeric_limits<float>::max();

    RenderHitInfo currentHit;
    bool wasHit = false;

    for (YAM::Triangle tri : mesh.GetTriangles()) {
        if (YAM::LinearMath::FindIntersection(ray, tri, currentHit)) {
            if (currentHit.distance < outHit.distance) {
                outHit = currentHit;
                outHit.material = &GetMaterial();

                wasHit = true;
            }
        }
    }

    return wasHit;
}

void MeshRenderable::Transform(const YAM::Mat4& mat4) {
    mesh.Transform(mat4);
}
