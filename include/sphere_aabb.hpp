#ifndef SPHERE_AABB_HPP
#define SPHERE_AABB_HPP
#include "structs.hpp"
bool intersect(const sphere& s, const aabb& b){
    using std::min;
    using std::max;
    using std::sqrt;
    vec3::Scalar x = max(b.start.x(), min(s.p.x(), b.end.x()));
    vec3::Scalar y = max(b.start.y(), min(s.p.y(), b.end.y()));
    vec3::Scalar z = max(b.start.z(), min(s.p.z(), b.end.z()));
    vec3::Scalar distancesq = (vec3(x, y, z) - s.p).squaredNorm();
    return distancesq < sq(s.r);
}
#endif