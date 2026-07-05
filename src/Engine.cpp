#include "Engine.hpp"
#include "AssetLoader.hpp"
#include "Input.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Engine::Engine()
    : window(nullptr), globalShader(nullptr), deltaTime(0.0f), lastFrame(0.0f),
      lastX(400.0f), lastY(300.0f), firstMouse(true) {
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

    Mesh cubeMesh = AssetLoader::loadMesh("models/cube.obj");
    GLuint cubeTexture = AssetLoader::loadTexture("models/cube.png");

    entities.push_back(Entity(cubeMesh, Vec3{0.0f, 0.0f, 0.0f}, cubeTexture));

    // Spin our cube slightly on start to confirm rotation math is active
    entities[0].rotation = Vec3{0.4f, 0.8f, 0.0f};

    lastFrame = static_cast<float>(glfwGetTime());

    return true;
}

void Engine::ProcessInput() {
    if (Input::IsPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    float speedModifier = 2.5f * deltaTime;
    float forward = 0.0f;
    float right = 0.0f;

    if (Input::IsPressed(GLFW_KEY_W)) forward += speedModifier;
    if (Input::IsPressed(GLFW_KEY_S)) forward -= speedModifier;
    if (Input::IsPressed(GLFW_KEY_D)) right += speedModifier;
    if (Input::IsPressed(GLFW_KEY_A)) right -= speedModifier;

    camera.Move(forward, right);
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

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        globalShader->use();

        Mat4 view = camera.GetViewMatrix();
        Mat4 proj = Mat4::Perspective(0.785398f, 800.0f / 600.0f, 0.1f, 100.0f);

        globalShader->setMat4("view", view.m);
        globalShader->setMat4("projection", proj.m);

        globalShader->setInt("texture1", 0);

        // Make the cube rotate dynamically in the scene loop over time
        if(!entities.empty()) {
            entities[0].rotation.y += 0.5f * deltaTime;
        }

        for (auto& entity : entities) {
            entity.Draw(*globalShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
