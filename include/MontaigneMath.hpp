#ifndef MONTAIGNEMATH_HPP
#define MONTAIGNEMATH_HPP
#include <cmath>

struct Vec3 { float x, y, z; };

struct Mat4 {
    float m[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

    static Mat4 Translation(float x, float y, float z) {
        Mat4 res; res.m[12] = x; res.m[13] = y; res.m[14] = z; return res;
    }

    static Mat4 LookAt(Vec3 pos, Vec3 target, Vec3 up) {
        Mat4 res;
        // Basic translation matrix to shift the world relative to camera
        res.m[12] = -pos.x; res.m[13] = -pos.y; res.m[14] = -pos.z;
        return res;
    }

    static Mat4 Perspective(float fov, float aspect, float near, float far) {
        Mat4 res;
        float f = 1.0f / tan(fov / 2.0f);
        res.m[0] = f / aspect; res.m[5] = f;
        res.m[10] = (far + near) / (near - far);
        res.m[11] = -1.0f; res.m[14] = (2.0f * far * near) / (near - far);
        return res;
    }
};
#endif
