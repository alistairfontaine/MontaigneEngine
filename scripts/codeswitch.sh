rm -f src/Engine.cpp && cat << 'EOF' > src/Engine.cpp
#include "Engine.hpp"
#include "AssetLoader.hpp"
#include "Input.hpp"
#include "Collision.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Engine::Engine()
    : window(nullptr), globalShader(nullptr), sharedCubeMesh{0, 0, 0}, sharedCubeTexture(0),
      deltaTime(0.0f), lastFrame(0.0f), lastX(400.0f), lastY(300.0f), firstMouse(true),
      spacePressedLastFrame(false) {
}

Engine::~Engine() {
    if (globalShader) {
        delete globalShader;
    }
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Engine::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Montaigne Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, Input::keyCallback);

    std::string vertCode, fragCode;
    std::ifstream vFile("src/shader.vert");
    std::ifstream fFile("src/shader.frag");

    if (!vFile.is_open() || !fFile.is_open()) {
        std::cerr << "Critical Error: Could not locate shader source text files in src/" << std::endl;
        return false;
    }

    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();
    vFile.close();
    fFile.close();

    vertCode = vStream.str();
    fragCode = fStream.str();

    globalShader = new Shader(vertCode.c_str(), fragCode.c_str());

    sharedCubeMesh = AssetLoader::loadMesh("models/cube.obj");
    sharedCubeTexture = AssetLoader::loadTexture("models/cube.png");

    for (int x = -3; x <= 3; ++x) {
        for (int z = -3; z <= 3; ++z) {
            Vec3 floorPos = Vec3{ static_cast<float>(x * 2.0f), -2.0f, static_cast<float>(z * 2.0f) };
            Vec3 floorScale = Vec3{ 0.95f, 0.1f, 0.95f };
            SpawnCube(floorPos, Vec3{0.0f, 0.0f, 0.0f}, floorScale);
        }
    }

    SpawnCube(Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.4f, 0.8f, 0.0f}, Vec3{1.0f, 1.0f, 1.0f});

    camera.pos = Vec3{0.0f, 0.0f, 5.0f};

    lastFrame = static_cast<float>(glfwGetTime());
    return true;
}

void Engine::SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale) {
    Entity newCube(sharedCubeMesh, position, sharedCubeTexture);
    newCube.rotation = rotation;
    newCube.scale = scale;
    entities.push_back(newCube);
}

void Engine::ProcessInput() {
    if (Input::IsPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    float speedModifier = 3.5f * deltaTime;
    float forward = 0.0f;
    float right = 0.0f;

    if (Input::IsPressed(GLFW_KEY_W)) forward += speedModifier;
    if (Input::IsPressed(GLFW_KEY_S)) forward -= speedModifier;
    if (Input::IsPressed(GLFW_KEY_D)) right += speedModifier;
    if (Input::IsPressed(GLFW_KEY_A)) right -= speedModifier;

    camera.Move(forward, right);

    if (Input::IsPressed(GLFW_KEY_SPACE)) {
        if (!spacePressedLastFrame) {
            float radYaw = camera.yaw * 0.0174533f;
            float radPitch = camera.pitch * 0.0174533f;

            Vec3 lookDir;
            lookDir.x = cos(radYaw) * cos(radPitch);
            lookDir.y = sin(radPitch);
            lookDir.z = sin(radYaw) * cos(radPitch);

            Vec3 spawnPos;
            spawnPos.x = camera.pos.x + lookDir.x * 3.0f;
            spawnPos.y = camera.pos.y + lookDir.y * 3.0f;
            spawnPos.z = camera.pos.z + lookDir.z * 3.0f;

            SpawnCube(spawnPos, Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.5f, 0.5f, 0.5f});
        }
        spacePressedLastFrame = true;
    } else {
        spacePressedLastFrame = false;
    }
}

void Engine::HandleMouseInput(double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.Rotate(xoffset, yoffset);
}

void Engine::Run() {
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        AABB playerBox;
        playerBox.minBounds = Vec3{ camera.pos.x - 0.25f, camera.pos.y - 1.5f, camera.pos.z - 0.25f };
        playerBox.maxBounds = Vec3{ camera.pos.x + 0.25f, camera.pos.y + 0.25f, camera.pos.z + 0.25f };

        for (const auto& entity : entities) {
            AABB entityBox = entity.GetBoundingBox();
            if (AABB::CheckIntersection(playerBox, entityBox)) {
                if (camera.pos.y use();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        float aspect = (height > 0) ? (static_cast<float>(width) / static_cast<float>(height)) : 1.0f;

        Mat4 view = camera.GetViewMatrix();
        Mat4 proj = Mat4::Perspective(0.785398f, aspect, 0.1f, 100.0f);

        globalShader->setMat4("view", view.m);
        globalShader->setMat4("projection", proj.m);
        globalShader->setVec3("viewPos", camera.pos.x, camera.pos.y, camera.pos.z);
        globalShader->setInt("texture1", 0);

        if (!entities.empty()) {
            entities.back().rotation.y += 0.5f * deltaTime;
        }

        for (auto& entity : entities) {
            entity.Draw(*globalShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
EOF
