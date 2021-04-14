#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include <cassert>
#include <cmath>
struct vec3{
    using Scalar = float;
    Scalar values[3];
    vec3(){}
    vec3(const Scalar& x, const Scalar& y, const Scalar& z) : values{x,y,z}{}
    const Scalar& x()const{
        return values[0];
    }
    const Scalar& y()const{
        return values[1];
    }
    const Scalar& z()const{
        return values[2];
    }
    Scalar& x(){
        return values[0];
    }
    Scalar& y(){
        return values[1];
    }
    Scalar& z(){
        return values[2];
    }
    Scalar dot(const vec3& o)const{
        return x() * o.x() + y() * o.y() + z() * o.z();
    }
    vec3 cross(const vec3& o)const{
        return vec3(y() * o.z() - z() * o.y(), z() * o.x() - x() * o.z(), x() * o.y() - y() * o.z());
    }
    const Scalar& operator()(unsigned i){
        assert(i < 3);
        return values[i];
    }
    Scalar squaredNorm()const{
        return dot(*this);
    }
    Scalar norm()const{
        using std::sqrt;
        return sqrt(squaredNorm());
    }
    void fill(const Scalar& x){
        values[0] = x;
        values[1] = x;
        values[2] = x;
    }
    void setZero(){
        fill(Scalar(0));
    }
    vec3  operator+ (const vec3& o)const{return vec3(x() + o.x(), y() + o.y(), z() + o.z());}
    vec3  operator- (const vec3& o)const{return vec3(x() - o.x(), y() - o.y(), z() - o.z());}
    vec3& operator+=(const vec3& o){*this = *this + o;return *this;}
    vec3& operator-=(const vec3& o){*this = *this - o;return *this;}
    vec3  operator*(const Scalar& o)const{return vec3(x() * o,y() * o, z() * o);}
    vec3  operator/(const Scalar& o)const{return vec3(x() / o,y() / o, z() / o);}
};
#endif