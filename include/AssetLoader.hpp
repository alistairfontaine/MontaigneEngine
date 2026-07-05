#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP
#include "Mesh.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

class AssetLoader {
public:
    static GLuint loadTexture(const char* path) {
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        int w, h, channels;
        unsigned char* data = stbi_load(path, &w, &h, &channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(data);
        return texID;
    }

    static Mesh loadMesh(const std::string& path) {
        (void)path;
        float vertices[] = {
            -0.5f,-0.5f,-0.5f, 0.0f,0.0f, 0.5f,-0.5f,-0.5f, 1.0f,0.0f, 0.5f,0.5f,-0.5f, 1.0f,1.0f, 0.5f,0.5f,-0.5f, 1.0f,1.0f, -0.5f,0.5f,-0.5f, 0.0f,1.0f, -0.5f,-0.5f,-0.5f, 0.0f,0.0f,
            -0.5f,-0.5f, 0.5f, 0.0f,0.0f, 0.5f,-0.5f, 0.5f, 1.0f,0.0f, 0.5f,0.5f, 0.5f, 1.0f,1.0f, 0.5f,0.5f, 0.5f, 1.0f,1.0f, -0.5f,0.5f, 0.5f, 0.0f,1.0f, -0.5f,-0.5f, 0.5f, 0.0f,0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f,0.0f, -0.5f, 0.5f,-0.5f, 1.0f,1.0f, -0.5f,-0.5f,-0.5f, 0.0f,1.0f, -0.5f,-0.5f,-0.5f, 0.0f,1.0f, -0.5f,-0.5f, 0.5f, 0.0f,0.0f, -0.5f, 0.5f, 0.5f, 1.0f,0.0f,
            0.5f, 0.5f, 0.5f, 1.0f,0.0f, 0.5f, 0.5f,-0.5f, 1.0f,1.0f, 0.5f,-0.5f,-0.5f, 0.0f,1.0f, 0.5f,-0.5f,-0.5f, 0.0f,1.0f, 0.5f,-0.5f, 0.5f, 0.0f,0.0f, 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
            -0.5f,-0.5f,-0.5f, 0.0f,1.0f, 0.5f,-0.5f,-0.5f, 1.0f,1.0f, 0.5f,-0.5f, 0.5f, 1.0f,0.0f, 0.5f,-0.5f, 0.5f, 1.0f,0.0f, -0.5f,-0.5f, 0.5f, 0.0f,0.0f, -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
            -0.5f, 0.5f,-0.5f, 0.0f,1.0f, 0.5f, 0.5f,-0.5f, 1.0f,1.0f, 0.5f, 0.5f, 0.5f, 1.0f,0.0f, 0.5f, 0.5f, 0.5f, 1.0f,0.0f, -0.5f, 0.5f, 0.5f, 0.0f,0.0f, -0.5f, 0.5f,-0.5f, 0.0f,1.0f
        };
        GLuint vbo; glGenBuffers(1, &vbo); glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        return { vbo, 36 };
    }
};
#endif
