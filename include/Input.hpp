#ifndef INPUT_HPP
#define INPUT_HPP
#include <GLFW/glfw3.h>
#include <map>

struct Input {
    static inline std::map<int, bool> keys;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        (void)window; (void)scancode; (void)mods;
        if (action == GLFW_PRESS) keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }
    static bool IsPressed(int key) { return keys[key]; }
};
#endif
