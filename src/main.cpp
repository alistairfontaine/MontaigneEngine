#include "Engine.hpp"
#include <iostream>

Engine* enginePtr = nullptr;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    (void)window;
    if (enginePtr) {
        enginePtr->HandleMouseInput(xpos, ypos);
    }
}

int main() {
    Engine engine;
    enginePtr = &engine;

    if (!engine.Initialize()) {
        std::cerr << "Critical Error: Failed to initiate MontaigneEngine context." << std::endl;
        return -1;
    }

    glfwSetCursorPosCallback(engine.window, mouseCallback);

    engine.Run();

    return 0;
}
