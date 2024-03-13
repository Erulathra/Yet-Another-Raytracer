#include "TGAWriter.h"

#include <array>
#include <fstream>

namespace YAR{
    void TGAWriter::Write(const std::string& path, const std::vector<uint32_t>& data, uint16_t width, uint16_t height) {
        const std::array<uint16_t, 9> fileHeader = {
            0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
            width, height,
            0x0820
        };

        std::fstream file(path, std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<const char*>(fileHeader.data()), fileHeader.size() * sizeof(uint16_t));
        file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint32_t));
        file.close();
    }
} // YAR
