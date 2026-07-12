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
#include "SpatialGrid.hpp"  // Integrated spatial partitioner header blueprint

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
    GLuint activeBuildTexture; // Phase M: Active hotbar building material container

    SpatialGrid spatialGrid; // Instantiated spatial mapping object layer


    Camera camera;

    float deltaTime;
    float lastFrame;

    double lastX;
    double lastY;
    bool firstMouse;

    float verticalVelocity;
    bool isGrounded;

    // Phase J: Real-time Raycast Trail Particle variables
    std::vector<Vec3> raycastTrailPoints;
    float raycastTrailTimer;

    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void ProcessInput();
    void HandleMouseInput(double xpos, double ypos);

    Entity* SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale, GLuint customTexture);
    Entity* GetEntityByID(int id);

    // Phase L: Persistent Disk Serialization Utility Functions
    void SaveWorld(const std::string& filename);
    void LoadWorld(const std::string& filename);

    // Phase N: Self-Contained Mathematical Procedural Noise Generator Mechanics
    float CalculateNoiseHeight(float x, float z) const;
};

#endif // ENGINE_HPP
