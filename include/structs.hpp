#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <array>
#include <type_traits>
#include <concepts>
#include <avx.hpp>
#include <cmath>
vec4d sqrt(const vec4d& x){
    vec4d ret;
    ret.data = _mm256_sqrt_pd(x.data);
    return ret;
}
vec8f sqrt(const vec8f& x){
    vec8f ret;
    ret.data = _mm256_sqrt_ps(x.data);
    return ret;
}
template<typename T>
auto rsqrt(const T& x){
    using std::sqrt;
    return 1.0 / sqrt(x);
}
template<>
auto rsqrt<vec8f>(const vec8f& x){
    vec8f ret;
    ret.data = _mm256_rsqrt_ps(x.data);
    return ret;
}
#if __has_include(<Eigen/Cored>) && ! defined(DONT_USE_EIGEN)
#include <Eigen/Core>
#include <Eigen/Geometry>
using vec3f = Eigen::Vector3f;
namespace Eigen{
template<>
    struct NumTraits<vec8f> : NumTraits<float>{};
}
template<typename T>
using vec3_tm = Eigen::Matrix<T, 3, 1>;
#else
#include "vector3.hpp"
using vec3f = vecn_tm<float, 3>;
template<typename T>
using vec3_tm = vecn_tm<T, 3>;
#endif
template<typename T>
concept is_primitive_scalar = std::is_same_v<std::remove_reference_t<std::remove_cv_t<T>>, float> || std::is_same_v<std::remove_reference_t<std::remove_cv_t<T>>, double>;
#define EPSILON 0.00006103515625
template<typename scalar>
struct intersection{
    vec3_tm<scalar> p;
    scalar t;
    scalar u;
    scalar v;
};
template<>
struct intersection<vec8f>{
    vec3_tm<vec8f> p;
    vec8f t;
    vec8f u;
    vec8f v;
    vec8i hitmask;
};
template<typename scalar>
struct double_intersection{
    std::pair<vec3_tm<scalar>, vec3_tm<scalar>> p;
    std::pair<scalar, scalar> t;
    scalar u;
    scalar v;
};
template<>
struct double_intersection<vec8f>{
    std::pair<vec3_tm<vec8f>, vec3_tm<vec8f>> p;
    std::pair<vec8f, vec8f> t;
    vec8f u;
    vec8f v;
    vec8i hitmask;
};
template<typename scalar>
struct ray{
    vec3_tm<scalar> o, d, id;
    ray(){}
    ray(const vec3_tm<scalar>& _o, const vec3_tm<scalar>& _d): o(_o), d(_d.normalized()){
        for(int i = 0;i < 3;i++){
            id(i) = scalar(1) / d(i);
        }
    }
};
template<typename scalar>
struct triangle{
    std::array<vec3_tm<scalar>, 3> vertices; 
    triangle(){}
    triangle(const vec3_tm<scalar>& _o, const vec3_tm<scalar>& _t, const vec3_tm<scalar>& t): vertices{_o, _t, t}{}
};
template<typename scalar>
struct sphere{
    vec3_tm<scalar> p;
    vec3_tm<scalar>::Scalar r;
};
template<typename scalar>
struct cylinder{
    vec3_tm<scalar> pa;
    vec3_tm<scalar> pb;
    vec3_tm<scalar>::Scalar r;
};
template<typename scalar>
struct aabb{
    vec3_tm<scalar> start;
    vec3_tm<scalar> end;
};
inline auto sq(const auto& x){
    return x * x;
}
#endif