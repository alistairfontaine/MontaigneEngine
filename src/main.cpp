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

Camera cam;
void mouseCallback(GLFWwindow* w, double x, double y) { cam.Rotate(x * 0.1f, -y * 0.1f); }

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Montaigne Engine - Final", NULL, NULL);
    glfwMakeContextCurrent(window); glewInit();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);

    glEnable(GL_DEPTH_TEST);
    Mesh cubeMesh = AssetLoader::loadMesh("cube.obj");
    std::vector<Entity> scene;
    Shader myShader(...); // (Same as previous build)

    while (!glfwWindowShouldClose(window)) {
        if (Input::IsPressed(GLFW_KEY_W)) cam.Move(0, -0.05f);
        if (Input::keys[GLFW_KEY_SPACE]) scene.emplace_back(cubeMesh, Vec3{0, 2, -5}, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(auto& e : scene) { e.Update(); e.Draw(myShader, 0); }

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
