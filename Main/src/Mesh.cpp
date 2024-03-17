#include "Mesh.h"

#include <cstdint>
#include <fstream>

#include "spdlog/spdlog.h"

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
            }
        }

        // create triangles
        for (int triangleID = 0; triangleID < (vert_indicies.size() / 3); ++triangleID) {
            uint32_t indiceID = triangleID * 3;
            
            uint32_t v1 = vert_indicies[indiceID] - 1;
            uint32_t v2 = vert_indicies[indiceID + 1] - 1;
            uint32_t v3 = vert_indicies[indiceID + 2] - 1;
            
            uint32_t n1 = norm_indicies[indiceID] - 1;
            uint32_t n2 = norm_indicies[indiceID + 1] - 1;
            uint32_t n3 = norm_indicies[indiceID + 2] - 1;
            
            trianges.emplace_back(
                verticies[v1],verticies[v2],verticies[v3],
                normals[n1],normals[n2],normals[n3]
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
} // YAR
