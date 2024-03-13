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

#define CALCULATE_COORDS (sizeX - x + sizeX * (sizeY - y))

        uint32_t GetPix(uint32_t x, uint32_t y) const { return colorBuf[CALCULATE_COORDS]; }
        void SetPix(uint32_t x, uint32_t y, uint32_t color) { colorBuf[CALCULATE_COORDS] = color; }

#undef CALCULATE_COORDS

        const std::vector<uint32_t>& GetData() { return colorBuf; }
    };
} // YAR
