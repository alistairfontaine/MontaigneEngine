#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Shader.hpp"
#include "../include/Input.hpp"
#include "../include/AssetLoader.hpp"
#include "../include/Camera.hpp"

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Montaigne Engine v0.1", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, Input::keyCallback);

    // Texture Setup
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    Mesh myMesh = AssetLoader::loadMesh("cube.obj");
    Camera mainCamera;

    Shader myShader(R"(#version 330 core
        layout(location=0) in vec3 aPos; layout(location=1) in vec2 aTex;
        uniform mat4 model; uniform mat4 view; uniform mat4 projection;
        out vec2 TexCoord;
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            TexCoord = aTex;
        })",
        R"(#version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;
        uniform sampler2D ourTexture;
        void main() {
            FragColor = texture(ourTexture, TexCoord);
        })");

    while (!glfwWindowShouldClose(window)) {
        if (Input::keys[GLFW_KEY_W]) mainCamera.Move(0, -0.05f);
        if (Input::keys[GLFW_KEY_S]) mainCamera.Move(0, 0.05f);
        if (Input::keys[GLFW_KEY_A]) mainCamera.Move(-0.05f, 0);
        if (Input::keys[GLFW_KEY_D]) mainCamera.Move(0.05f, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.use();

        myShader.setMat4("model", Mat4::RotationZ((float)glfwGetTime()).m);
        myShader.setMat4("view", mainCamera.GetViewMatrix().m);
        myShader.setMat4("projection", Mat4::Perspective(1.0f, 800.0f/600.0f, 0.1f, 100.0f).m);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindBuffer(GL_ARRAY_BUFFER, myMesh.VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, myMesh.vertexCount);
        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
