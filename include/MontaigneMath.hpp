#ifndef MONTAIGNE_MATH_HPP
#define MONTAIGNE_MATH_HPP

#include <cmath>

struct Vec3 {
    float x, y, z;
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    static Vec3 Cross(Vec3 a, Vec3 b) {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    static float Dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    Vec3 Normalized() {
        float len = sqrt(x*x + y*y + z*z);
        return {x/len, y/len, z/len};
    }
};

struct Mat4 {
    float m[16];
    static Mat4 Identity() { return {{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }}; }

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

    static Mat4 RotationZ(float angle) {
        float c = cos(angle), s = sin(angle);
        return {{ c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }};
    }

    static Mat4 LookAt(Vec3 eye, Vec3 target, Vec3 up) {
        Vec3 f = (target - eye).Normalized();
        Vec3 r = Vec3::Cross(f, up).Normalized();
        Vec3 u = Vec3::Cross(r, f);
        return {{ r.x, u.x, -f.x, 0, r.y, u.y, -f.y, 0, r.z, u.z, -f.z, 0, -Vec3::Dot(r, eye), -Vec3::Dot(u, eye), Vec3::Dot(f, eye), 1 }};
    }
};

#endif
