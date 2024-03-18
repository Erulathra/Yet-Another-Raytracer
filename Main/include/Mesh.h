#pragma once

#include <vector>

#include "LinearMath.h"

namespace YAM{
    class Mat4;
}

namespace YAR {

class Mesh {
private:
    std::vector<YAM::Triangle> trianges;
    
    YAM::AABB boudingBox;
    
public:
    Mesh(const std::string& path);

    const std::vector<YAM::Triangle>& GetTriangles() const { return trianges; }
    const YAM::AABB& GetBoudingBox() const { return boudingBox; }
    
    void Transform(const YAM::Mat4& mat);
private:
    void ParseOBJ(const std::string& path);
    void CalculateBoundingBox(const std::vector<YAM::Vector3>& verticies);

};

} // YAR
