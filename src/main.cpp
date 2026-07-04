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
#include <cstdlib> // For rand()

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Montaigne Engine - Scene Editor", NULL, NULL);
    glfwMakeContextCurrent(window); glewInit();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glfwSetKeyCallback(window, Input::keyCallback);

    Mesh cubeMesh = AssetLoader::loadMesh("cube.obj");
    std::vector<Entity> scene;
    scene.push_back(Entity(cubeMesh, {0.0f, 0.0f, -5.0f}, 1.0f));

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

    Camera cam;
    bool spacePressed = false; // Debounce for spawning

    while (!glfwWindowShouldClose(window)) {
        if (Input::keys[GLFW_KEY_W]) cam.Move(0, -0.05f);
        if (Input::keys[GLFW_KEY_S]) cam.Move(0, 0.05f);
        if (Input::keys[GLFW_KEY_A]) cam.Move(-0.05f, 0);
        if (Input::keys[GLFW_KEY_D]) cam.Move(0.05f, 0);

        // Scene Editor: Spawn object
        if (Input::keys[GLFW_KEY_SPACE] && !spacePressed) {
            float rx = ((float)rand()/(float)RAND_MAX) * 4.0f - 2.0f;
            float ry = ((float)rand()/(float)RAND_MAX) * 4.0f - 2.0f;
            scene.push_back(Entity(cubeMesh, {rx, ry, -5.0f}, 1.0f + (float)(rand()%5)));
            spacePressed = true;
        }
        if (!Input::keys[GLFW_KEY_SPACE]) spacePressed = false;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myShader.use();
        myShader.setMat4("view", cam.GetViewMatrix().m);
        myShader.setMat4("projection", Mat4::Perspective(1.5f, 800.0f/600.0f, 0.1f, 100.0f).m);

        for(auto& e : scene) e.Draw(myShader, (float)glfwGetTime());

        glfwSwapBuffers(window); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
