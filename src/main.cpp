#include "../include/Engine.hpp"

Engine* enginePtr;
void mouseCallback(GLFWwindow* w, double x, double y) { (void)w; enginePtr->cam.Rotate((float)x * 0.1f, (float)-y * 0.1f); }

int main() {
    Engine engine;
    enginePtr = &engine;
    glfwSetCursorPosCallback(engine.window, mouseCallback);

    // Set Input Callback as well
    glfwSetKeyCallback(engine.window, Input::keyCallback);

    engine.Run();
    return 0;
}
