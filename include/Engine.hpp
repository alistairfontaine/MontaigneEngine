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
    bool spaceHeld = false; double lastX = 400.0, lastY = 300.0; GLuint texture;

    Engine() {
        glfwInit();
        window = glfwCreateWindow(800, 600, "Montaigne", NULL, NULL);
        glfwMakeContextCurrent(window);
        glewInit();
        glEnable(GL_DEPTH_TEST);

        const char* v = "#version 330 core\n"
                        "layout(location=0) in vec3 p;\n"
                        "layout(location=1) in vec2 t;\n"
                        "layout(location=2) in vec3 n;\n"
                        "uniform mat4 m,v,p_mat;\n"
                        "out vec2 texC;\n"
                        "out vec3 norm;\n"
                        "void main(){\n"
                        "  gl_Position = p_mat * v * m * vec4(p, 1.0);\n"
                        "  texC = t;\n"
                        "  norm = mat3(transpose(inverse(m))) * n;\n"
                        "}";

        const char* f = "#version 330 core\n"
                        "uniform sampler2D s;\n"
                        "in vec2 texC;\n"
                        "in vec3 norm;\n"
                        "out vec4 fC;\n"
                        "void main(){\n"
                        "  vec3 lightDir = normalize(vec3(1.0, 2.0, 1.0));\n"
                        "  float diff = max(dot(normalize(norm), lightDir), 0.2);\n"
                        "  fC = texture(s, texC) * diff;\n"
                        "}";

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

            // Spawning from sky to trigger collision mechanics
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spaceHeld) {
                // Drop slightly offset on a repeating pattern so you can build structures
                float xOffset = (float)(scene.size() % 3) * 0.5f - 0.5f;
                scene.emplace_back(cube, Vec3{xOffset, 5.0f, -5.0f});
                spaceHeld = true;
            } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) spaceHeld = false;

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader->use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            shader->setInt("s", 0);

            shader->setMat4("v", cam.GetViewMatrix().m);
            shader->setMat4("p_mat", Mat4::Perspective(45.0f * (3.14159f/180.0f), 800.0f/600.0f, 0.1f, 100.0f).m);

            for(auto& e : scene) { e.Update(scene); e.Draw(*shader); }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};
#endif
