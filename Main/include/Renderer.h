#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace YAR{
    class Buffer;
    class Camera;
}

namespace YAR {

    class Renderer {
    private:
        std::unique_ptr<Buffer> colorBuffer;

    public:
        Renderer(uint32_t sizeX, uint32_t sizeY);
        ~Renderer();

        void Render(const Camera* camera) const;
        void Save(const std::string& path) const;
    };

} // SG
