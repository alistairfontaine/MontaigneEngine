#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map> // Swapped to map for memory stability
#include "Entity.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Engine {
public:
    GLFWwindow* window;
    Shader* globalShader;

    // Stable scene graph lookup container
    std::map<int, Entity> entities;

    int nextEntityID;
    int centerpieceID;

    Mesh sharedCubeMesh;
    GLuint sharedCubeTexture;

    Camera camera;
    float deltaTime;
    float lastFrame;

    double lastX;
    double lastY;
    bool firstMouse;
    bool spacePressedLastFrame;

    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void ProcessInput();
    void HandleMouseInput(double xpos, double ypos);

    Entity* SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale);
    Entity* GetEntityByID(int id);
};

#endif // ENGINE_HPP
