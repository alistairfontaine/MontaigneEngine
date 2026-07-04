#ifndef MONTAIGNE_MATH_HPP
#define MONTAIGNE_MATH_HPP

struct Vec3 {
    float x, y, z;

    // Basic operator overloading for vector arithmetic
    Vec3 operator+(const Vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
};

struct Mat4 {
    float m[16]; // 4x4 matrix, column-major for OpenGL compatibility

    // Identity matrix constructor
    static Mat4 Identity() {
        return {{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }};
    }
};

#endif
