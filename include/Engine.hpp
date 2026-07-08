#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <vector>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Entity.hpp"

class Engine {
public:
    GLFWwindow* window;
    Shader* globalShader;

    std::map<int, Entity> entities;

    int nextEntityID;
    int centerpieceID;

    Mesh sharedCubeMesh;
    GLuint sharedCubeTexture;
    GLuint sharedFloorTexture;

    Camera camera;
    float deltaTime;
    float lastFrame;

    double lastX;
    double lastY;
    bool firstMouse;

    float verticalVelocity;
    bool isGrounded;

    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void ProcessInput();
    void HandleMouseInput(double xpos, double ypos);

    Entity* SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale, GLuint customTexture);
    Entity* GetEntityByID(int id);
};

#endif // ENGINE_HPP
