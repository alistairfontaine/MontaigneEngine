#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"
#include <cmath>

struct Camera {
    Vec3 pos = {0, 0, 5};
    float yaw = -90.0f, pitch = 0.0f;
    float fov = 45.0f;

    void Rotate(float dx, float dy) {
        yaw += dx; pitch += dy;
        if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    }

    void Move(float forward, float right) {
        pos.x += (cos(yaw * 0.01745f) * forward + sin(yaw * 0.01745f) * right) * 0.1f;
        pos.z += (sin(yaw * 0.01745f) * forward - cos(yaw * 0.01745f) * right) * 0.1f;
    }

    Mat4 GetViewMatrix() {
        return Mat4::Translation(-pos.x, -pos.y, -pos.z);
    }
};
#endif
