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
    Camera mainCamera;
    Shader myShader(R"(#version 330 core
        layout(location=0) in vec3 aPos;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() { gl_Position = projection * view * model * vec4(aPos, 1.0); })",
        "#version 330 core\nout vec4 FragColor;\nvoid main(){FragColor=vec4(0.2,0.8,0.5,1.0);}");

    Mat4 projection = Mat4::Perspective(1.0f, 800.0f/600.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        // Navigation Logic
        if (Input::keys[GLFW_KEY_W]) mainCamera.Move(0, -0.05f);
        if (Input::keys[GLFW_KEY_S]) mainCamera.Move(0, 0.05f);
        if (Input::keys[GLFW_KEY_A]) mainCamera.Move(-0.05f, 0);
        if (Input::keys[GLFW_KEY_D]) mainCamera.Move(0.05f, 0);

        glClear(GL_COLOR_BUFFER_BIT);
        myShader.use();

        float angle = (float)glfwGetTime();
        Mat4 model = Mat4::RotationZ(angle);

        myShader.setMat4("model", model.m);
        myShader.setMat4("view", mainCamera.GetViewMatrix().m);
        myShader.setMat4("projection", projection.m);

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
