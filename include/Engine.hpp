#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "AssetLoader.hpp"

class Engine {
public:
    GLFWwindow* window;
    Camera cam;
    std::vector<Entity> scene;
    Shader* shader;
    GLuint textureID;
    bool spaceHeld = false;

    Engine() {
        if (!glfwInit()) std::cout << "GLFW Init Failed!" << std::endl;
        window = glfwCreateWindow(800, 600, "Montaigne Engine - Final", NULL, NULL);
        glfwMakeContextCurrent(window);
        glewInit();
        glEnable(GL_DEPTH_TEST);

        shader = new Shader(R"(#version 330 core
            layout(location=0) in vec3 aPos; layout(location=1) in vec2 aTex;
            uniform mat4 model; uniform mat4 view; uniform mat4 projection;
            out vec2 TexCoord;
            void main() { gl_Position = projection * view * model * vec4(aPos, 1.0); TexCoord = aTex; })",
            R"(#version 330 core
            in vec2 TexCoord; out vec4 FragColor; uniform sampler2D tex;
            void main() { FragColor = texture(tex, TexCoord); })");

        glGenTextures(1, &textureID); glBindTexture(GL_TEXTURE_2D, textureID);
        int w, h, c; unsigned char* d = stbi_load("texture.jpg", &w, &h, &c, 0);
        if(!d) { std::cout << "CRITICAL: texture.jpg not found!" << std::endl; }
        else { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, d); glGenerateMipmap(GL_TEXTURE_2D); stbi_image_free(d); }
        shader->use(); shader->setInt("tex", 0);
    }

    void Run() {
        Mesh cube = AssetLoader::loadMesh("cube.obj");
        while (!glfwWindowShouldClose(window)) {
            if (Input::IsPressed(GLFW_KEY_W)) cam.Move(1.0f, 0.0f);
            if (Input::IsPressed(GLFW_KEY_S)) cam.Move(-1.0f, 0.0f);
            if (Input::IsPressed(GLFW_KEY_A)) cam.Move(0.0f, -1.0f);
            if (Input::IsPressed(GLFW_KEY_D)) cam.Move(0.0f, 1.0f);

            if (Input::IsPressed(GLFW_KEY_SPACE)) {
                if (!spaceHeld && scene.size() < 200) {
                    // Added jitter to spawn position so they don't overlap perfectly
                    float rx = (float)(rand() % 20 - 10) * 0.1f;
                    float rz = (float)(rand() % 20 - 10) * 0.1f - 5.0f;
                    scene.emplace_back(cube, Vec3{rx, 5.0f, rz}, 1.0f);
                    spaceHeld = true;
                }
            } else spaceHeld = false;

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader->use();
            shader->setMat4("view", cam.GetViewMatrix().m);
            shader->setMat4("projection", Mat4::Perspective(45.0f * (3.14f/180.0f), 800.0f/600.0f, 0.1f, 100.0f).m);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
            for(auto& e : scene) { e.Update(); e.Draw(*shader); }

            glfwSwapBuffers(window); glfwPollEvents();
        }
    }

    ~Engine() { delete shader; glfwTerminate(); }
};
#endif
