#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"

struct Camera {
    Vec3 pos = {0,0,0};
    float yaw = -90.0f, pitch = 0.0f;
    void Rotate(float xOffset, float yOffset) {
        yaw += xOffset; pitch += yOffset;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }
    Mat4 GetViewMatrix() {
        // Returns the camera transformation matrix
        return Mat4::LookAt(pos, {0,0,-1}, {0,1,0});
    }
    void Move(float x, float z) { pos.x += x; pos.z += z; }
};
#endif
