#include "Mesh.h"

#include <cstdint>
#include <fstream>
#include <spdlog/spdlog.h>

#include "Vector4.h"
#include "Vector3.h"
#include "Mat4.h"

namespace YAR{
    Mesh::Mesh(const std::string& path) {
        ParseOBJ(path);
    }

    void Mesh::ParseOBJ(const std::string& path) {
        std::ifstream objFile{path};

        std::vector<YAM::Vector3> verticies{};
        std::vector<uint32_t> vert_indicies{};
        
        std::vector<YAM::Vector3> normals{};
        std::vector<uint32_t> norm_indicies{};
        
        std::vector<YAM::Vector3> uvs{};
        std::vector<uint32_t> uv_indicies{};

        // Parse file
        std::string fileLine;
        while (std::getline(objFile, fileLine)) {
            
            // skip comments
            if (fileLine[0] == '#') {
                continue;
            }

            char command[3];
            char parameters[30];

            std::sscanf(fileLine.c_str(), "%s %[^\t\n]", command, parameters);
            
            if (strcmp(command, "v") == 0) {
                YAM::Vector3 vertex;
                std::sscanf(parameters, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                verticies.push_back(vertex);
            }
            if (strcmp(command, "vn") == 0) {
                YAM::Vector3 normal;
                std::sscanf(parameters, "%f %f %f", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            }
            if (strcmp(command, "vt") == 0) {
                YAM::Vector3 uv{0};
                std::sscanf(parameters, "%f %f", &uv.x, &uv.y);
                uvs.push_back(uv);
            }
            if (strcmp(command, "f") == 0) {
                uint32_t v1, v2, v3;
                uint32_t t1, t2, t3;
                uint32_t n1, n2, n3;

                std::sscanf(parameters,
                           "%i/%i/%i %i/%i/%i %i/%i/%i",
                           &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                vert_indicies.push_back(v1);
                vert_indicies.push_back(v2);
                vert_indicies.push_back(v3);
                
                norm_indicies.push_back(n1);
                norm_indicies.push_back(n2);
                norm_indicies.push_back(n3);

                uv_indicies.push_back(t1);
                uv_indicies.push_back(t2);
                uv_indicies.push_back(t3);
            }
        }

        // create triangles
        spdlog::info("{} {}", vert_indicies.size(), norm_indicies.size());
        
        for (int triangleID = 0; triangleID < std::trunc(vert_indicies.size() / 3); ++triangleID) {
            uint32_t indiceID = triangleID * 3;
            
            const uint32_t v1 = vert_indicies[indiceID] - 1;
            const uint32_t v2 = vert_indicies[indiceID + 1] - 1;
            const uint32_t v3 = vert_indicies[indiceID + 2] - 1;
            
            const uint32_t n1 = norm_indicies[indiceID] - 1;
            const uint32_t n2 = norm_indicies[indiceID + 1] - 1;
            const uint32_t n3 = norm_indicies[indiceID + 2] - 1;
            
            const uint32_t t1 = uv_indicies[indiceID] - 1;
            const uint32_t t2 = uv_indicies[indiceID + 1] - 1;
            const uint32_t t3 = uv_indicies[indiceID + 2] - 1;

            trianges.emplace_back(
                verticies[v1],verticies[v2],verticies[v3],
                normals[n1],normals[n2],normals[n3],
                uvs[t1], uvs[t2],uvs[t3]
                );
        }
        
        CalculateBoundingBox(verticies);
    }

    void Mesh::CalculateBoundingBox(const std::vector<YAM::Vector3>& verticies) {
        for (const YAM::Vector3& vertex : verticies) {
            boudingBox.min.x = std::min(boudingBox.min.x, vertex.x);
            boudingBox.min.y = std::min(boudingBox.min.y, vertex.y);
            boudingBox.min.z = std::min(boudingBox.min.z, vertex.z);

            boudingBox.max.x = std::max(boudingBox.max.x, vertex.x);
            boudingBox.max.y = std::max(boudingBox.max.y, vertex.y);
            boudingBox.max.z = std::max(boudingBox.max.z, vertex.z);
        }
    }

    void Mesh::Transform(const YAM::Mat4& mat) {
        const YAM::Mat4 normalTranslation = mat.ClearTranslation().Inverse().Transpose();
        
        for (YAM::Triangle& triange : trianges) {
            triange.posA = YAM::Vector3(mat * YAM::Vector4(triange.posA, 1.f));
            triange.posB = YAM::Vector3(mat * YAM::Vector4(triange.posB, 1.f));
            triange.posC = YAM::Vector3(mat * YAM::Vector4(triange.posC, 1.f));
            
            triange.norA = YAM::Vector3(normalTranslation * YAM::Vector4(triange.norA, 1.f));
            triange.norB = YAM::Vector3(normalTranslation * YAM::Vector4(triange.norB, 1.f));
            triange.norC = YAM::Vector3(normalTranslation * YAM::Vector4(triange.norC, 1.f));
        }

        boudingBox.min = YAM::Vector3(mat * YAM::Vector4(boudingBox.min, 1.f));
        boudingBox.max = YAM::Vector3(mat * YAM::Vector4(boudingBox.max, 1.f));
    }
} // YAR
