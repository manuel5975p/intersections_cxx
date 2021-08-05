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

template<typename scalar> 
    requires(is_primitive_scalar<scalar>) 
std::optional<std::pair<double_intersection<scalar>, vec3_tm<scalar>>> intersect_with_normal(const ray<scalar>& r, const aabb<scalar>& b) {
    scalar tmin = -INFINITY, tmax = INFINITY;
    using std::max;
    using std::min;

    int dim_hit = -1;
    for (int i = 0; i < 3; ++i) {
        scalar t1 = (b.start(i) - r.o(i)) * r.id(i);
        scalar t2 = (b.end(i)   - r.o(i)) * r.id(i);
        auto tminold = tmin;
        tmin = max(tmin, min(t1, t2));
        if constexpr(is_primitive_scalar<scalar>){
            if(tmin != tminold){
                dim_hit = i;
            }
        }
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
    vec3_tm<scalar> normal;
    if(dim_hit == 0){
        normal = vec3_tm<scalar>(1, 0, 0) * (std::signbit(r.d.x()) ? 1 : -1);
    }
    if(dim_hit == 1){
        normal = vec3_tm<scalar>(0, 1, 0) * (std::signbit(r.d.x()) ? 1 : -1);
    }
    if(dim_hit == 2){
        normal = vec3_tm<scalar>(0, 0, 1) * (std::signbit(r.d.x()) ? 1 : -1);
    }
    return std::make_pair(ret, normal);
}
#endif