#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"
#include <cmath>

struct Camera {
    Vec3 pos = {0, 0, 5};
    float yaw = -90.0f, pitch = 0.0f;

    void Rotate(float dx, float dy) {
        yaw += dx; pitch += dy;
        if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    }

    void Move(float forward, float right) {
        float radYaw = yaw * 0.01745f;
        pos.x += (cos(radYaw) * forward + sin(radYaw) * right) * 0.1f;
        pos.z += (sin(radYaw) * forward - cos(radYaw) * right) * 0.1f;
    }

    Mat4 GetViewMatrix() {
        // Calculate the forward vector based on Euler angles
        Vec3 front;
        front.x = cos(yaw * 0.01745f) * cos(pitch * 0.01745f);
        front.y = sin(pitch * 0.01745f);
        front.z = sin(yaw * 0.01745f) * cos(pitch * 0.01745f);

        // Target is current position + direction
        Vec3 target = {pos.x + front.x, pos.y + front.y, pos.z + front.z};
        // Use standard Up vector
        Vec3 up = {0, 1, 0};

        return Mat4::LookAt(pos, target, up);
    }
};
#endif
