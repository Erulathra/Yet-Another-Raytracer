#pragma once

#include <cstdint>
#include <vector>

namespace YAR{
    class Buffer {
    private:
        std::vector<uint32_t> colorBuf;

        const uint32_t sizeX;
        const uint32_t sizeY;

    public:
        Buffer(uint32_t sizeX, uint32_t sizeY);
        ~Buffer();

        uint32_t GetSizeX() const { return sizeX; }
        uint32_t GetSizeY() const { return sizeY; }

        void FillColor(uint32_t color);

        uint32_t GetPix(uint32_t x, uint32_t y) const { return colorBuf[x + sizeX * y]; }
        void SetPix(uint32_t x, uint32_t y, uint32_t color) { colorBuf[x + sizeX * y] = color; }

        const std::vector<uint32_t>& GetData() { return colorBuf; }
    };
} // YAR
