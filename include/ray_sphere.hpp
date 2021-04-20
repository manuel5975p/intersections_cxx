#ifndef RAY_SPHERE_HPP
#define RAY_SPHERE_HPP
#include "structs.hpp"
template<typename scalar>
intersection<scalar> intersect(const ray<scalar>& r, const sphere<scalar>& s)
    requires (!is_primitive_scalar<scalar>)
{
    intersection<scalar> ret;
    scalar a = scalar(-2.0f) * r.d.dot(r.o - s.p);
    scalar D = sq(scalar(2.0f) * r.d.dot(r.o - s.p)) - scalar(4.0f) * r.d.squaredNorm()*((r.o - s.p).squaredNorm() - sq(s.r));
    scalar denom = scalar(2.0f) * r.d.squaredNorm();
    ret.hitmask = (D < 0);
    ret.t = (a - sqrt(D)) / denom;
    ret.p = r.o + r.d * ret.t;
    return ret;
}
template<typename scalar>
std::optional<intersection<scalar>> intersect(const ray<scalar>& r, const sphere<scalar>& s)
    requires is_primitive_scalar<scalar>
{
    using std::asin;
    using std::atan2;
    using std::sqrt;
    intersection<scalar> ret;
    scalar a = -2 * r.d.dot(r.o - s.p);
    scalar D = sq(2 * r.d.dot(r.o - s.p)) - 4* r.d.squaredNorm()*((r.o - s.p).squaredNorm() - sq(s.r));
    scalar denom = 2 * r.d.squaredNorm();
    if(D < 0) return std::nullopt;
    if(D == 0){
        ret.t = a / denom;
        ret.p = r.o + r.d * ret.t;
        vec3_tm<scalar> d = (ret.p - s.p).normalized();
        ret.u = 0.5f + (atan2(d.y(), d.x()) / (2 * M_PI));
        ret.v = 0.5f - (asin(d.z()) / M_PI);
        return ret;
    }
    ret.t = (a - sqrt(D)) / denom;
    ret.p = r.o + r.d * ret.t;
    vec3_tm<scalar> d = (ret.p - s.p).normalized();
    ret.u = 0.5f + (atan2(d.y(), d.x()) / (2 * M_PI));
    ret.v = 0.5f - (asin(d.z()) / M_PI);
    return ret;
}
#endif