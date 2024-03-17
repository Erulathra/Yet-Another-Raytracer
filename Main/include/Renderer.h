#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace YAR {
    class Renderable;
    class Buffer;
    class Camera;

    class Renderer {
    private:
        std::unique_ptr<Buffer> colorBuffer;

        std::vector<std::shared_ptr<Renderable>> renderables;

    public:
        Renderer(uint32_t sizeX, uint32_t sizeY);
        ~Renderer();

        void AddRenderable(const std::shared_ptr<Renderable>& renderable);

        void Render(const Camera* camera) const;
        void Save(const std::string& path) const;
    };

} // SG
