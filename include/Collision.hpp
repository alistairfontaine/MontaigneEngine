#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "MontaigneMath.hpp"

struct AABB {
    Vec3 minBounds;
    Vec3 maxBounds;

    // Checks intersecting overlap conditions across all three coordinate axes
    static bool CheckIntersection(const AABB& a, const AABB& b) {
        return (a.minBounds.x <= b.maxBounds.x && a.maxBounds.x >= b.minBounds.x) &&
               (a.minBounds.y <= b.maxBounds.y && a.maxBounds.y >= b.minBounds.y) &&
               (a.minBounds.z <= b.maxBounds.z && a.maxBounds.z >= b.minBounds.z);
    }
};

#endif // COLLISION_HPP
