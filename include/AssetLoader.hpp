#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

struct Mesh { GLuint VBO; int vertexCount; };

class AssetLoader {
public:
    static Mesh loadMesh(const std::string& path) {
        std::vector<float> tempV, tempVT, finalV;
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 2) == "v ") {
                std::istringstream s(line.substr(2));
                float x, y, z; s >> x >> y >> z;
                tempV.push_back(x); tempV.push_back(y); tempV.push_back(z);
            } else if (line.substr(0, 3) == "vt ") {
                std::istringstream s(line.substr(3));
                float u, v; s >> u >> v;
                tempVT.push_back(u); tempVT.push_back(v);
            } else if (line.substr(0, 2) == "f ") {
                std::istringstream s(line.substr(2));
                for(int i=0; i<3; ++i) {
                    std::string part; s >> part;
                    size_t slash = part.find('/');
                    int vIdx = std::stoi(part.substr(0, slash)) - 1;
                    int vtIdx = std::stoi(part.substr(slash + 1)) - 1;

                    finalV.push_back(tempV[vIdx*3]);
                    finalV.push_back(tempV[vIdx*3+1]);
                    finalV.push_back(tempV[vIdx*3+2]);
                    finalV.push_back(tempVT[vtIdx*2]);
                    finalV.push_back(tempVT[vtIdx*2+1]);
                }
            }
        }
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, finalV.size() * sizeof(float), finalV.data(), GL_STATIC_DRAW);
        return {VBO, (int)(finalV.size() / 5)};
    }
};
#endif
