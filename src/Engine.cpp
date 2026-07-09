#include "AssetLoader.hpp" // Load asset systems globally first
#include "Engine.hpp"
#include "Input.hpp"
#include "Collision.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Engine::Engine()
    : window(nullptr), globalShader(nullptr), nextEntityID(0), centerpieceID(-1),
      sharedCubeMesh{0, 0, 0}, sharedCubeTexture(0), sharedFloorTexture(0), deltaTime(0.0f), lastFrame(0.0f),
      lastX(400.0f), lastY(300.0f), firstMouse(true), verticalVelocity(0.0f), isGrounded(false) {
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

    // Load your distinct floor tile texture asset map
    sharedFloorTexture = AssetLoader::loadTexture("models/floor.png");

    // Build stable 7x7 structural floor tile map using the dedicated floor texture
    for (int x = -3; x <= 3; ++x) {
        for (int z = -3; z <= 3; ++z) {
            Vec3 floorPos = Vec3{ static_cast<float>(x * 2.0f), -2.0f, static_cast<float>(z * 2.0f) };
            Vec3 floorScale = Vec3{ 0.95f, 0.1f, 0.95f };
            SpawnCube(floorPos, Vec3{0.0f, 0.0f, 0.0f}, floorScale, sharedFloorTexture);
        }
    }

    // Main centerpiece retains your red-and-black skull texture
    Entity* centerCube = SpawnCube(Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.4f, 0.8f, 0.0f}, Vec3{1.0f, 1.0f, 1.0f}, sharedCubeTexture);

    if (centerCube) {
        centerpieceID = centerCube->id;
    }

    camera.pos = Vec3{0.0f, 0.0f, 5.0f};
    lastFrame = static_cast<float>(glfwGetTime());
    return true;
}

Entity* Engine::SpawnCube(Vec3 position, Vec3 rotation, Vec3 scale, GLuint customTexture) {
    int id = nextEntityID++;
    // Kept your exact emplace logic, only swapping the trailing variable parameter
    auto result = entities.emplace(id, Entity(id, sharedCubeMesh, position, customTexture));

    Entity& newCube = result.first->second;
    newCube.rotation = rotation;
    newCube.scale = scale;
    return &newCube;
}

Entity* Engine::GetEntityByID(int id) {
    auto it = entities.find(id);
    if (it != entities.end()) {
        return &(it->second);
    }
    return nullptr;
}

void Engine::ProcessInput() {
    if (Input::IsPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    // Adjusting speed to feel smooth and responsive when multiplied inside your camera move loops
    float speedModifier = 25.0f * deltaTime;
    float forward = 0.0f;
    float right = 0.0f;

    if (Input::IsPressed(GLFW_KEY_W)) forward += speedModifier;
    if (Input::IsPressed(GLFW_KEY_S)) forward -= speedModifier;
    if (Input::IsPressed(GLFW_KEY_D)) right += speedModifier;
    if (Input::IsPressed(GLFW_KEY_A)) right -= speedModifier;

    camera.Move(forward, right);

    // Dynamic vertical impulse force jump mechanic
    if (Input::IsPressed(GLFW_KEY_SPACE) && isGrounded) {
        verticalVelocity = 4.5f;
        isGrounded = false;
    }

    // Secondary cube particle spawner safely re-routed onto your 'E' key
    static bool ePressedLastFrame = false;
    if (Input::IsPressed(GLFW_KEY_E)) {
        if (!ePressedLastFrame) {
            float radYaw = camera.yaw * 0.0174533f;
            float radPitch = camera.pitch * 0.0174533f;
            Vec3 lookDir;
            lookDir.x = cos(radYaw) * cos(radPitch);
            lookDir.y = sin(radPitch);
            lookDir.z = sin(radYaw) * cos(radPitch);

            Vec3 spawnPos = camera.pos + (lookDir * 3.0f);
            SpawnCube(spawnPos, Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.5f, 0.5f, 0.5f}, sharedCubeTexture);

        }
        ePressedLastFrame = true;
    } else {
        ePressedLastFrame = false;
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

        // --- PHASE E: GUARDED SPAWNED OBJECT KINEMATICS ---
        float gravity = -9.81f;

        // Process gravity and mutual stacking checks ONLY for newly spawned cubes
        for (auto& pair : entities) {
            Entity& currentEntity = pair.second;

            // Failsafe condition check: Lock floor slabs (0-48) and center cube firmly in place
            if (currentEntity.id <= centerpieceID) {
                continue;
            }

            // Apply acceleration velocities strictly to the custom box instances
            currentEntity.velocity.y += gravity * deltaTime;
            currentEntity.position.y += currentEntity.velocity.y * deltaTime;

            AABB currentBox = currentEntity.GetBoundingBox();
            for (const auto& otherPair : entities) {
                const Entity& otherEntity = otherPair.second;
                if (currentEntity.id == otherEntity.id) continue;

                AABB otherBox = otherEntity.GetBoundingBox();
                if (AABB::CheckIntersection(currentBox, otherBox)) {
                    if (currentEntity.position.y > otherEntity.position.y) {
                        currentEntity.position.y = otherBox.maxBounds.y + currentEntity.scale.y;
                        currentEntity.velocity.y = 0.0f;
                    }
                }
            }
        }

        // PRESERVED VERBATIM: Your original working player movement physics loop
        camera.pos.y -= 4.0f * deltaTime;
        AABB playerBox;
        playerBox.minBounds = Vec3{ camera.pos.x - 0.25f, camera.pos.y - 1.25f, camera.pos.z - 0.25f };
        playerBox.maxBounds = Vec3{ camera.pos.x + 0.25f, camera.pos.y + 0.25f, camera.pos.z + 0.25f };
        for (const auto& pair : entities) {
            AABB entityBox = pair.second.GetBoundingBox();
            if (AABB::CheckIntersection(playerBox, entityBox)) {
                if (camera.pos.y < entityBox.maxBounds.y + 1.25f) {
                    camera.pos.y = entityBox.maxBounds.y + 1.25f;
                }
            }
        }
        // --------------------------------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        globalShader->use();

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

        Entity* focalCube = GetEntityByID(centerpieceID);
        if (focalCube) {
            focalCube->rotation.y += 0.5f * deltaTime;
        }

        // Loop map elements securely via structured iteration pairs
        for (auto& pair : entities) {
            pair.second.Draw(*globalShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
