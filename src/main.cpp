#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Shader.hpp"
#include "../include/Input.hpp"
#include "../include/AssetLoader.hpp"
#include "../include/Camera.hpp"
#include <iostream>

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Montaigne Engine v0.1", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetKeyCallback(window, Input::keyCallback);

    Mesh myTriangle = AssetLoader::loadTriangle();
    Shader myShader(R"(#version 330 core
        layout(location=0) in vec3 aPos;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() { gl_Position = projection * view * model * vec4(aPos, 1.0); })",
        "#version 330 core\nout vec4 FragColor;\nvoid main(){FragColor=vec4(0.2,0.8,0.5,1.0);}");

    float identity[] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        myShader.use();

        // Passing the 3D matrices to the GPU
        myShader.setMat4("model", identity);
        myShader.setMat4("view", identity);
        myShader.setMat4("projection", identity);

        glBindBuffer(GL_ARRAY_BUFFER, myTriangle.VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, myTriangle.vertexCount);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
