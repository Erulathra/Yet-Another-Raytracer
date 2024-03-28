#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "LinearMath.h"

namespace YAR{
class Texture {
private:
    std::vector<uint32_t> colorBuf;

    int32_t sizeX;
    int32_t sizeY;
    
public:
    Texture(const std::string& path);

    uint32_t GetPix(int32_t x, int32_t y) const { return colorBuf[x + sizeX * y]; }
    YAM::Color Sample(const YAM::Vector3& UV) const;
private:
    void Load(const std::string& path);
    
    void SetPix(int32_t x, int32_t y, uint32_t color) { colorBuf[x + sizeX * y] = color; }
};
    
}
