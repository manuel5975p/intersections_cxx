#ifndef RAY_CYLINDER_HPP
#define RAY_CYLINDER_HPP
#include "structs.hpp"
#include <optional>
template<typename scalar>
intersection<scalar> intersect(const ray<scalar>& r, const cylinder<scalar>& c)
    requires (!is_primitive_scalar<scalar>)
{
    using std::abs;
    using std::sqrt;
    using std::fabs;
    intersection<scalar> ret;
    vec3_tm<scalar> ca = c.pb-c.pa;
    vec3_tm<scalar> oc = r.o-c.pa;
    scalar tmp = ca.dot(ca);
    scalar card = ca.dot(r.d);
    scalar caoc = ca.dot(oc);
    scalar a = tmp - card*card;
    scalar b = tmp * oc.dot(r.d) - caoc*card;
    scalar _c = tmp * oc.dot(oc) - caoc*caoc - c.r*c.r*tmp;
    scalar h = b*b - a*_c;
    ret.hitmask = h >= 0.0;
    h = sqrt(h);
    scalar t = (-b - h)/a;
    scalar y = caoc + t * card;
    auto bodybranch = (y > scalar(0.0)) & (y < tmp);
    auto capbranch = abs(b + a * t) < h;
    scalar bodyt = t;
    t = ((bitcast_to_float(y < 0.0) & tmp) - caoc) / card;
    t = ((t & bitcast_to_float(capbranch)) | (bodyt & bitcast_to_float(bodybranch)));
    ret.p = r.o + r.d * t;
    ret.hitmask = (bodybranch | capbranch) & ret.hitmask;
    ret.t = t;
    return ret;
}
template<typename scalar>
std::optional<intersection<scalar>> intersect(const ray<scalar>& r, const cylinder<scalar>& c)
    requires is_primitive_scalar<scalar>
{
    using std::abs;
    using std::sqrt;
    using std::fabs;
    intersection<scalar> ret;
    vec3_tm<scalar> ca = c.pb-c.pa;
    vec3_tm<scalar> oc = r.o-c.pa;
    scalar tmp = ca.dot(ca);
    scalar card = ca.dot(r.d);
    scalar caoc = ca.dot(oc);
    scalar a = tmp - card*card;
    scalar b = tmp * oc.dot(r.d) - caoc*card;
    scalar _c = tmp * oc.dot(oc) - caoc*caoc - c.r*c.r*tmp;
    scalar h = b*b - a*_c;
    if( h<0.0 ) return std::nullopt; //no intersection
    h = sqrt(h);
    scalar t = (-b-h)/a;
    // body
    scalar y = caoc + t*card;
    if(y > 0.0 && y < tmp){
        ret.t = t;
        ret.p = r.o + r.d * t;//
        return ret;
        //return vec4( t, (oc+t*r.d-ca*y/caca)/ra );
    }
    // caps
    t = (((y < 0.0) ? 0.0 : tmp) - caoc) / card;
    if(abs(b + a * t) < h){
        ret.t = t;
        ret.p = r.o + r.d * t;
        return ret;
        //return vec4( t, ca*(y > 0 ? 1 : -1)/caca );
    }
    return std::nullopt;
}

#endif