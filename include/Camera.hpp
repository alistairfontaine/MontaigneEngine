#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "MontaigneMath.hpp"

class Camera {
public:
    Mat4 GetViewMatrix() { return Mat4::Identity(); }
};
#endif
