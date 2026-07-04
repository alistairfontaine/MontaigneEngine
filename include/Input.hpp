#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

class Input {
public:
    static inline bool keys[1024] = {false}; // 'inline' solves the linker error

    static void keyCallback(GLFWwindow*, int key, int, int action, int) {
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) keys[key] = true;
            else if (action == GLFW_RELEASE) keys[key] = false;
        }
    }
};

#endif
