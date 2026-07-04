#ifndef MONTAIGNE_MATH_HPP
#define MONTAIGNE_MATH_HPP

#include <cmath>

struct Mat4 {
    float m[16];
    static Mat4 Identity() {
        return {{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }};
    }

    // Rotation Matrix (Z-axis spin)
    static Mat4 RotationZ(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return {{ c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }};
    }
};

#endif
