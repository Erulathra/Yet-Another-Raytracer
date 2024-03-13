//
// Created by erulathra on 13.03.24.
//

#include "Buffer.h"

namespace YAR{
    Buffer::Buffer(uint32_t sizeX, uint32_t sizeY)
        : sizeX(sizeX)
          , sizeY(sizeY) {
        colorBuf.resize(sizeX * sizeY);
    }

    Buffer::~Buffer() = default;

    void Buffer::FillColor(uint32_t color) {
        for (int colorID = 0; colorID < sizeX * sizeY; ++colorID) {
            colorBuf[colorID] = color;
        }
    }
} // YAR
