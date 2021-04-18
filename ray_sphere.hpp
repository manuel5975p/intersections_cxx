#ifndef RAY_SPHERE_HPP
#define RAY_SPHERE_HPP
#include "structs.hpp"
std::optional<intersection> intersect(const ray& r, const sphere& s){
    using std::asin;
    using std::atan2;
    intersection ret;
    using scalar = vec3::Scalar;
    scalar a = -2 * r.d.dot(r.o - s.p);
    scalar D = sq(2 * r.d.dot(r.o - s.p)) - 4* r.d.squaredNorm()*((r.o - s.p).squaredNorm() - sq(s.r));
    scalar denom = 2 * r.d.squaredNorm();
    if(D < 0) return std::nullopt;
    if(D == 0){
        ret.t = a / denom;
        ret.p = r.o + r.d * ret.t;
        vec3 d = (ret.p - s.p).normalized();
        ret.u = 0.5f + (atan2(d.y(), d.x()) / (2 * M_PI));
        ret.v = 0.5f - (asin(d.z()) / M_PI);
        return ret;
    }
    ret.t = (a - D) / denom;
    ret.p = r.o + r.d * ret.t;
    vec3 d = (ret.p - s.p).normalized();
    ret.u = 0.5f + (atan2(d.y(), d.x()) / (2 * M_PI));
    ret.v = 0.5f - (asin(d.z()) / M_PI);
    return ret;
}
#endif