#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP
#include <GL/glew.h>

struct Mesh { GLuint VBO; int vertexCount; };

class AssetLoader {
public:
    static Mesh loadTriangle() {
        float vertices[] = { -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  0.0f, 0.5f, 0.0f };
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        return {VBO, 3};
    }
};
#endif
