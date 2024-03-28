#include "Buffer.h"

namespace YAR{
    Buffer::Buffer(uint32_t sizeX, uint32_t sizeY)
        : sizeX(sizeX)
          , sizeY(sizeY) {
        colorBuf.resize(sizeX * sizeY);
    }

    Buffer::~Buffer() = default;

    void Buffer::FillColor(uint32_t color) {
        for (int i = 0; i < sizeX * sizeY; ++i) {
            colorBuf[i] = color;
        }
    }
} // YAR
