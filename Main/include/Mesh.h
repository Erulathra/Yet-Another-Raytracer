#pragma once

#include <vector>

#include "LinearMath.h"
#include "Vector3.h"

namespace YAR {

class Mesh {
private:
    std::vector<YAM::Triangle> trianges;
    
public:
    Mesh(const std::string& path);

    const std::vector<YAM::Triangle>& GetTriangles() const { return trianges; }
    
private:
    void ParseOBJ(const std::string& path);
};

} // YAR
