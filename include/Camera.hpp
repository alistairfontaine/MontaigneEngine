#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"
#include <cmath>

struct Camera {
    Vec3 pos = {0, 0, 5};
    float yaw = -90.0f, pitch = 0.0f;
    float fov = 45.0f;

    void Move(float forward, float right) {
        // Calculate movement based on rotation
        pos.x += (cos(yaw * 0.01745f) * forward + sin(yaw * 0.01745f) * right) * 0.1f;
        pos.z += (sin(yaw * 0.01745f) * forward - cos(yaw * 0.01745f) * right) * 0.1f;
    }

    // ... keep Rotate() and GetViewMatrix() ...
};
#endif
