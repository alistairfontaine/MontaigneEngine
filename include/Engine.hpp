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

    // Global shared graphics resource registers
    Mesh sharedCubeMesh;
    GLuint sharedCubeTexture;

    // Core timing tracking configurations
    Camera camera;
    float deltaTime;
    float lastFrame;

    // Peripheral tracking records
    double lastX;
    double lastY;
    bool firstMouse;

    // Track state to prevent a single tap from spawning 100 cubes per second
    bool spacePressedLastFrame;

    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void ProcessInput();
    void HandleMouseInput(double xpos, double ypos);
    void SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale);
};

#endif // ENGINE_HPP
