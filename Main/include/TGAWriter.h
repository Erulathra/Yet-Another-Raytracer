#pragma once

#include <string>
#include <stdint.h>
#include <vector>

namespace YAR {

class TGAWriter {
public:
    void static Write(const std::string& path, const std::vector<uint32_t>& data, uint16_t width, uint16_t height);
};

}
