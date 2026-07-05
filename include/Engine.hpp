#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Entity.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Engine {
public:
    GLFWwindow* window;
    Shader* globalShader;
    std::vector<Entity> entities;

    // Core camera and timing states
    Camera camera;
    float deltaTime;
    float lastFrame;

    // Mouse movement states
    double lastX;
    double lastY;
    bool firstMouse;

    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void ProcessInput();
    void HandleMouseInput(double xpos, double ypos);
};

#endif // ENGINE_HPP
