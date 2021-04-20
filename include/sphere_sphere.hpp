#ifndef SPHERE_SPHERE_HPP
#define SPHERE_SPHERE_HPP
#include "structs.hpp"
template<typename scalar>
auto intersect(const sphere<scalar>& s1, const sphere<scalar>& s2){
    return (s1.p - s2.p).squaredNorm() < sq(s1.r + s2.r);
}
#endif