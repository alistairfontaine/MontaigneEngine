#ifndef MONTAIGNE_MATH_HPP
#define MONTAIGNE_MATH_HPP

#include <cmath>

struct Vec3 {
    float x, y, z;
};

struct Mat4 {
    float m[16];

    static Mat4 Identity() {
        return {{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }};
    }

    // Perspective Projection: Defines the "lens" of the camera
    static Mat4 Perspective(float fov, float aspect, float near, float far) {
        float tanHalfFov = tan(fov / 2.0f);
        Mat4 res = {0};
        res.m[0] = 1.0f / (aspect * tanHalfFov);
        res.m[5] = 1.0f / tanHalfFov;
        res.m[10] = -(far + near) / (far - near);
        res.m[11] = -1.0f;
        res.m[14] = -(2.0f * far * near) / (far - near);
        return res;
    }
};

#endif
