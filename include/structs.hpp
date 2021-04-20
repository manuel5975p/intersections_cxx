#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#if __has_include(<Eigen/Core>) && ! defined(DONT_USE_EIGEN)
#include <Eigen/Core>
#include <Eigen/Geometry>
using vec3 = Eigen::Vector3f;
namespace Eigen{
template<>
    struct NumTraits<vec8f> : NumTraits<float>{};
}
#else
#include "vector3.hpp"
using vec3 = vecn_tm<float, 3>;
#endif
#define EPSILON 0.00001

struct intersection{
    vec3 p;
    vec3::Scalar t;
    vec3::Scalar u;
    vec3::Scalar v;
};

struct double_intersection{
    vec3 p;
    std::pair<vec3::Scalar, vec3::Scalar> t;
    vec3::Scalar u;
    vec3::Scalar v;
};
struct ray{
    vec3 o, d, id;
    ray(){}
    ray(const vec3& _o, const vec3& _d): o(_o), d(_d / _d.norm()){
        for(int i = 0;i < 3;i++){
            id(i) = vec3::Scalar(1) / d(i);
        }
    }
};
struct triangle{
    vec3 vertices[3];
    triangle(){}
    triangle(const vec3& _o, const vec3& _t, const vec3& t): vertices{_o, _t, t}{}
};
struct sphere{
    vec3 p;
    vec3::Scalar r;
};
struct cylinder{
    vec3 pa;
    vec3 pb;
    vec3::Scalar r;
};
struct aabb{
    vec3 start;
    vec3 end;
};
inline auto sq(const auto& x){
    return x * x;
}
#endif