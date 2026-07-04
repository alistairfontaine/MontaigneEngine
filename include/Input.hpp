#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

class Input {
public:
    static bool keys[1024];

    // By removing the variable names for unused params, the compiler stops complaining
    static void keyCallback(GLFWwindow*, int key, int, int action, int) {
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) keys[key] = true;
            else if (action == GLFW_RELEASE) keys[key] = false;
        }
    }
};

bool Input::keys[1024] = {false};

#endif
