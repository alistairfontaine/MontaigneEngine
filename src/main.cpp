#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Shader.hpp"
#include "../include/Input.hpp"
#include "../include/AssetLoader.hpp"
#include "../include/Camera.hpp"
#include "../include/Entity.hpp"
#include "../include/MontaigneMath.hpp"
#include <vector>
#include <cstdlib>

Camera cam;
void mouseCallback(GLFWwindow* w, double x, double y) { (void)w; cam.Rotate((float)x * 0.1f, (float)-y * 0.1f); }
void scrollCallback(GLFWwindow* w, double x, double y) { (void)w; cam.fov -= (float)y; if(cam.fov < 1.0f) cam.fov = 1.0f; }

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Montaigne Engine - Stable", NULL, NULL);
    glfwMakeContextCurrent(window); glewInit();
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glEnable(GL_DEPTH_TEST);

    Mesh cubeMesh = AssetLoader::loadMesh("cube.obj");
    std::vector<Entity> scene;
    bool spaceHeld = false;

    // Simple Shader (No Lighting)
    Shader myShader(R"(#version 330 core
        layout(location=0) in vec3 aPos; layout(location=1) in vec2 aTex;
        uniform mat4 model; uniform mat4 view; uniform mat4 projection;
        out vec2 TexCoord;
        void main() { gl_Position = projection * view * model * vec4(aPos, 1.0); TexCoord = aTex; })",
        R"(#version 330 core
        in vec2 TexCoord; out vec4 FragColor; uniform sampler2D tex;
        void main() { FragColor = texture(tex, TexCoord); })");

    GLuint t; glGenTextures(1, &t); glBindTexture(GL_TEXTURE_2D, t);
    int w, h, c; unsigned char* d = stbi_load("texture.jpg", &w, &h, &c, 0);
    if(d) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, d); glGenerateMipmap(GL_TEXTURE_2D); stbi_image_free(d); }
    myShader.use(); myShader.setInt("tex", 0);

    while (!glfwWindowShouldClose(window)) {
        if (Input::IsPressed(GLFW_KEY_W)) cam.Move(1.0f, 0.0f);
        if (Input::IsPressed(GLFW_KEY_S)) cam.Move(-1.0f, 0.0f);
        if (Input::IsPressed(GLFW_KEY_A)) cam.Move(0.0f, -1.0f);
        if (Input::IsPressed(GLFW_KEY_D)) cam.Move(0.0f, 1.0f);

        if (Input::IsPressed(GLFW_KEY_SPACE)) {
            if (!spaceHeld && scene.size() < 200) { scene.emplace_back(cubeMesh, Vec3{(float)(rand()%10-5), 5.0f, -5.0f}, 1.0f); spaceHeld = true; }
        } else spaceHeld = false;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();
        myShader.setMat4("view", cam.GetViewMatrix().m);
        myShader.setMat4("projection", Mat4::Perspective(cam.fov * (3.14f/180.0f), 800.0f/600.0f, 0.1f, 100.0f).m);

        glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, t);
        for(auto& e : scene) { e.Update(); e.Draw(myShader); }

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
