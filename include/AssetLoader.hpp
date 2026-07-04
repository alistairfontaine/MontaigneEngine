#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

struct Mesh { GLuint VBO; int vertexCount; };

class AssetLoader {
public:
    static Mesh loadMesh(const std::string& path) {
        std::vector<float> tempV, finalV;
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 2) == "v ") {
                std::istringstream s(line.substr(2));
                float x, y, z; s >> x >> y >> z;
                tempV.push_back(x); tempV.push_back(y); tempV.push_back(z);
            } else if (line.substr(0, 2) == "f ") {
                std::istringstream s(line.substr(2));
                int i1, i2, i3; s >> i1 >> i2 >> i3;

                // Add vertices
                for (int i : {i1, i2, i3}) {
                    finalV.push_back(tempV[(i-1)*3]);
                    finalV.push_back(tempV[(i-1)*3+1]);
                    finalV.push_back(tempV[(i-1)*3+2]);
                }
            }
        }
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, finalV.size() * sizeof(float), finalV.data(), GL_STATIC_DRAW);
        return {VBO, (int)(finalV.size() / 3)};
    }
};
#endif
