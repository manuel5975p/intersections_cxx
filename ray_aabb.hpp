#ifndef RAY_AABB_HPP
#define RAY_AABB_HPP
#include "structs.hpp"
template<typename intersection_t = double_intersection>
std::optional<intersection_t> intersect(const ray& r, const aabb& b) {
    using scalar = vec3::Scalar;
    scalar tmin = -INFINITY, tmax = INFINITY;
    using std::max;
    using std::min;
    for (int i = 0; i < 3; ++i) {
        scalar t1 = (b.start(i) - r.o(i)) * r.id(i);
        scalar t2 = (b.end(i)   - r.o(i)) * r.id(i);
        tmin = max(tmin, min(t1, t2));
        tmax = min(tmax, max(t1, t2));
    }
    intersection_t ret;
    
    if constexpr(std::is_same_v<intersection_t, double_intersection>){
        if(tmax < tmin)return std::nullopt;
        ret.t.first = tmin;
        ret.t.second = tmax;
        ret.p = r.o + r.d * tmin;
        ret.u = 0;
        ret.v = 0;
        return std::make_optional(ret);
    }
    else{
        if(tmax < tmin)return std::nullopt;
        ret.t = tmin;
        ret.p = r.o + r.d * ret.t;
        ret.u = 0;
        ret.v = 0;
        return (tmax >= tmin) ? std::make_optional(ret) : std::nullopt;
    }
    
}
#endif