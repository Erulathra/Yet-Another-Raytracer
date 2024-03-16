//
// Created by erulathra on 13.03.24.
//

#include "Buffer.h"

namespace YAR{
    Buffer::Buffer(uint32_t sizeX, uint32_t sizeY)
        : sizeX(sizeX)
          , sizeY(sizeY) {
        colorBuf.resize(sizeX * sizeY);
        depth.resize(sizeX * sizeY);
    }

    Buffer::~Buffer() = default;

    void Buffer::FillColor(uint32_t color) {
        for (int i = 0; i < sizeX * sizeY; ++i) {
            colorBuf[i] = color;
        }
    }

    void Buffer::FillDepth(float value) {
        for (int i = 0; i < sizeX * sizeY; ++i) {
            depth[i] = value;
        }
    }
} // YAR
