#ifndef RAY_CYLINDER_HPP
#define RAY_CYLINDER_HPP
#include "structs.hpp"
#include <optional>
std::optional<intersection> intersect(const ray& r, const cylinder& c ){
    using std::abs;
    using std::fabs;
    intersection ret;
    vec3 ca = c.pb-c.pa;
    vec3 oc = r.o-c.pa;
    vec3::Scalar tmp = ca.dot(ca);
    vec3::Scalar card = ca.dot(r.d);
    vec3::Scalar caoc = ca.dot(oc);
    vec3::Scalar a = tmp - card*card;
    vec3::Scalar b = tmp * oc.dot(r.d) - caoc*card;
    vec3::Scalar _c = tmp * oc.dot(oc) - caoc*caoc - c.r*c.r*tmp;
    vec3::Scalar h = b*b - a*_c;
    if( h<0.0 ) return std::nullopt; //no intersection
    h = sqrt(h);
    vec3::Scalar t = (-b-h)/a;
    // body
    vec3::Scalar y = caoc + t*card;
    if( y>0.0 && y<tmp ){
        ret.t = t;
        ret.p = r.o + r.d * t;//
        return ret;
        //return vec4( t, (oc+t*r.d-ca*y/caca)/ra );
    }
    // caps
    t = (((y<0.0)?0.0:tmp) - caoc)/card;
    if( abs(b+a*t)<h ){
        ret.t = t;
        ret.p = r.o + r.d * t;
        return ret;
        //return vec4( t, ca*(y > 0 ? 1 : -1)/caca );
    }
    return std::nullopt;
}

#endif