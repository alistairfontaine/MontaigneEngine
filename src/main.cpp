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
    glfwMakeContextCurrent(window); glewInit();
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, Input::keyCallback);

    Mesh myMesh = AssetLoader::loadMesh("cube.obj");
    Camera mainCamera;

    // Shader with basic Diffuse lighting
Shader myShader(R"(#version 330 core
        layout(location=0) in vec3 aPos;
        uniform mat4 model; uniform mat4 view; uniform mat4 projection;
        out vec3 FragPos;
        void main() {
            FragPos = vec3(model * vec4(aPos, 1.0));
            gl_Position = projection * view * vec4(FragPos, 1.0);
        })",
        R"(#version 330 core
        in vec3 FragPos;
        out vec4 FragColor;
        uniform vec3 lightPos;
        void main() {
            // Calculate normal based on surface derivative
            vec3 norm = normalize(cross(dFdx(FragPos), dFdy(FragPos)));
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.2);
            FragColor = vec4(0.8 * diff, 0.2 * diff, 0.5 * diff, 1.0);
        })");

    Mat4 projection = Mat4::Perspective(1.0f, 800.0f/600.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        if (Input::keys[GLFW_KEY_W]) mainCamera.Move(0, -0.05f);
        if (Input::keys[GLFW_KEY_S]) mainCamera.Move(0, 0.05f);
        if (Input::keys[GLFW_KEY_A]) mainCamera.Move(-0.05f, 0);
        if (Input::keys[GLFW_KEY_D]) mainCamera.Move(0.05f, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.use();

        myShader.setMat4("model", Mat4::RotationZ((float)glfwGetTime()).m);
        myShader.setMat4("view", mainCamera.GetViewMatrix().m);
        myShader.setMat4("projection", projection.m);
        // Set light position
        glUniform3f(glGetUniformLocation(myShader.ID, "lightPos"), 2.0f, 5.0f, 2.0f);

        glBindBuffer(GL_ARRAY_BUFFER, myMesh.VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, myMesh.vertexCount);

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
