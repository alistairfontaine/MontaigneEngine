#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"

class Camera {
public:
    Vec3 pos = {0.0f, 0.0f, 2.0f};
    Vec3 target = {0.0f, 0.0f, 0.0f};
    Vec3 up = {0.0f, 1.0f, 0.0f};

    void Move(float dx, float dz) {
        pos.x += dx;
        pos.z += dz;
    }

    Mat4 GetViewMatrix() { return Mat4::LookAt(pos, target, up); }
};
#endif
