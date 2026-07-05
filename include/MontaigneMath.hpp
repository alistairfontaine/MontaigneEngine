#ifndef MONTAIGNE_MATH_HPP
#define MONTAIGNE_MATH_HPP
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator-(const Vec3& o) const {
        return {x - o.x, y - o.y, z - o.z};
    }

    static Vec3 Normalize(Vec3 v) {
        float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (len > 0.0f) {
            v.x /= len; v.y /= len; v.z /= len;
        }
        return v;
    }

    static Vec3 Cross(Vec3 a, Vec3 b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    static float Dot(Vec3 a, Vec3 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
};

struct Mat4 {
    float m[16] = {1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1};

    static Mat4 Translation(float x, float y, float z) {
        Mat4 res;
        res.m[12] = x; res.m[13] = y; res.m[14] = z;
        return res;
    }

    static Mat4 LookAt(Vec3 pos, Vec3 target, Vec3 up) {
        // Calculate camera coordinate system axis vectors
        Vec3 f = Vec3::Normalize(target - pos);      // Forward vector
        Vec3 s = Vec3::Normalize(Vec3::Cross(f, up)); // Right vector
        Vec3 u = Vec3::Cross(s, f);                  // True Up vector

        Mat4 res;
        // First Column (X-axis basis)
        res.m[0] = s.x;
        res.m[1] = u.x;
        res.m[2] = -f.x;
        res.m[3] = 0.0f;

        // Second Column (Y-axis basis)
        res.m[4] = s.y;
        res.m[5] = u.y;
        res.m[6] = -f.y;
        res.m[7] = 0.0f;

        // Third Column (Z-axis basis)
        res.m[8] = s.z;
        res.m[9] = u.z;
        res.m[10] = -f.z;
        res.m[11] = 0.0f;

        // Fourth Column (Translation components combined with rotation orientation)
        res.m[12] = -Vec3::Dot(s, pos);
        res.m[13] = -Vec3::Dot(u, pos);
        res.m[14] =  Vec3::Dot(f, pos);
        res.m[15] = 1.0f;

        return res;
    }

    static Mat4 Perspective(float fov, float aspect, float near, float far) {
        Mat4 res;
        float f = 1.0f / tan(fov / 2.0f);
        res.m[0] = f / aspect;
        res.m[5] = f;
        res.m[10] = (far + near) / (near - far);
        res.m[11] = -1.0f;
        res.m[14] = (2.0f * far * near) / (near - far);
        res.m[15] = 0.0f; // Standard perspective requirement for W component division
        return res;
    }
};
#endif
