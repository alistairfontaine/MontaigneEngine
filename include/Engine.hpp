#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Entity.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "AssetLoader.hpp"

class Engine {
public:
    GLFWwindow* window; Camera cam; std::vector<Entity> scene; Shader* shader;
    bool spaceHeld = false; double lastX = 400.0, lastY = 300.0;
    GLuint texture;

    Engine() {
        glfwInit(); window = glfwCreateWindow(800, 600, "Montaigne", NULL, NULL);
        glfwMakeContextCurrent(window); glewInit(); glEnable(GL_DEPTH_TEST);
        const char* v = "#version 330 core\nlayout(location=0) in vec3 p; layout(location=1) in vec2 t; uniform mat4 m,v,p_mat; out vec2 texC; void main(){ gl_Position = p_mat * v * m * vec4(p, 1.0); texC = t; }";
        const char* f = "#version 330 core\nuniform sampler2D s; in vec2 texC; out vec4 fC; void main(){ fC = texture(s, texC); }";
        shader = new Shader(v, f);
        texture = AssetLoader::loadTexture("cube.png");
    }

    void Run() {
        Mesh cube = AssetLoader::loadMesh("cube.obj");
        while (!glfwWindowShouldClose(window)) {
            float s = 0.1f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cam.Move(s, 0);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cam.Move(-s, 0);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cam.Move(0, -s);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cam.Move(0, s);
            double x, y; glfwGetCursorPos(window, &x, &y);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
                cam.Rotate((float)(x - lastX) * 0.1f, (float)(lastY - y) * 0.1f);
            lastX = x; lastY = y;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spaceHeld) {
                scene.emplace_back(cube, Vec3{(float)(scene.size() % 10) * 1.5f - 7.5f, 0, -5.0f}); spaceHeld = true;
            } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) spaceHeld = false;
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader->use(); glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture); shader->setInt("s", 0);
            shader->setMat4("v", cam.GetViewMatrix().m);
            shader->setMat4("p_mat", Mat4::Perspective(45.0f * (3.14159f/180.0f), 800.0f/600.0f, 0.1f, 100.0f).m);
            for(auto& e : scene) { e.Update(scene); e.Draw(*shader); }
            glfwSwapBuffers(window); glfwPollEvents();
        }
    }
};
#endif
