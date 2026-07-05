#ifndef MONTAIGNE_CAMERA_HPP
#define MONTAIGNE_CAMERA_HPP

#include "MontaigneMath.hpp"
#include <cmath>

struct Camera {
    Vec3 pos = {0.0f, 0.0f, 5.0f};
    float yaw = -90.0f, pitch = 0.0f;

    void Rotate(float dx, float dy) {
        yaw += dx;
        pitch += dy;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    void Move(float forward, float right) {
        float radYaw = yaw * 0.0174533f;
        pos.x += (cos(radYaw) * forward + sin(radYaw) * right) * 0.1f;
        pos.z += (sin(radYaw) * forward - cos(radYaw) * right) * 0.1f;
    }

    Mat4 GetViewMatrix() {
        Vec3 front;
        front.x = cos(yaw * 0.0174533f) * cos(pitch * 0.0174533f);
        front.y = sin(pitch * 0.0174533f);
        front.z = sin(yaw * 0.0174533f) * cos(pitch * 0.0174533f);

        Vec3 target = {pos.x + front.x, pos.y + front.y, pos.z + front.z};
        Vec3 up = {0.0f, 1.0f, 0.0f};

        return Mat4::LookAt(pos, target, up);
    }
};

#endif
