#ifndef RAY_AABB_HPP
#define RAY_AABB_HPP
#include "structs.hpp"
template<typename scalar>
std::conditional_t<is_primitive_scalar<scalar>, std::optional<double_intersection<scalar>>,double_intersection<scalar>>
intersect(const ray<scalar>& r, const aabb<scalar>& b) {
    scalar tmin = -INFINITY, tmax = INFINITY;
    using std::max;
    using std::min;
    for (int i = 0; i < 3; ++i) {
        scalar t1 = (b.start(i) - r.o(i)) * r.id(i);
        scalar t2 = (b.end(i)   - r.o(i)) * r.id(i);
        tmin = max(tmin, min(t1, t2));
        tmax = min(tmax, max(t1, t2));
    }
    double_intersection<scalar> ret;
    if constexpr(is_primitive_scalar<scalar>)
        if(tmax < tmin){
            return std::nullopt;
        }
    if constexpr(!is_primitive_scalar<scalar>)
        ret.hitmask = tmax >= tmin;
    
    ret.t.first = tmin;
    ret.t.second = tmax;
    ret.p.first = r.o + r.d * tmin;
    ret.p.second = r.o + r.d * tmax;
    ret.u = 0;
    ret.v = 0;
    return ret;
}
#endif