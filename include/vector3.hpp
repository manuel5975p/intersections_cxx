#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include <array>
#include <cassert>
#include <cmath>
template<typename _scalar, size_t _n>
struct vecn_tm{
    using Scalar = _scalar;
    constexpr static size_t n = _n;
    std::array<Scalar, n> values;
    vecn_tm(){}
    vecn_tm(const Scalar& x){}
    vecn_tm(const Scalar& x, const Scalar& y, const Scalar& z) : values{x,y,z}{}
    const Scalar& x()const{
        assert(n > 0);
        return values[0];
    }
    const Scalar& y()const{
        assert(n > 1);
        return values[1];
    }
    const Scalar& z()const{
        assert(n > 2);
        return values[2];
    }
    const Scalar& w()const{
        assert(n > 3);
        return values[3];
    }
    Scalar& x(){
        assert(n > 0);
        return values[0];
    }
    Scalar& y(){
        assert(n > 1);
        return values[1];
    }
    Scalar& z(){
        assert(n > 2);
        return values[2];
    }
    Scalar& w(){
        assert(n > 3);
        return values[3];
    }
    Scalar dot(const vecn_tm<Scalar, n>& o)const{
        return x() * o.x() + y() * o.y() + z() * o.z();
    }
    template<typename otherscalar>
    vecn_tm cross(const vecn_tm<otherscalar, n>& o)const{
        static_assert(n == 3, Cross only works for n = 3);
        return vecn_tm(y() * o.z() - z() * o.y(), z() * o.x() - x() * o.z(), x() * o.y() - y() * o.z());
    }
    const Scalar& operator()(unsigned i)const{
        assert(i < n);
        return values[i];
    }
    Scalar& operator()(unsigned i){
        assert(i < n);
        return values[i];
    }
    Scalar squaredNorm()const{
        return dot(*this);
    }
    Scalar norm()const{
        using std::sqrt;
        return sqrt(squaredNorm());
    }
    vecn_tm normalized()const{
        Scalar isqrt = Scalar(1) / norm();
        return *this * isqrt;
    }
    void fill(const Scalar& x){
        std::fill(values.begin(), values.end(), x);
    }
    void setZero(){
        fill(Scalar(0));
    }
    vecn_tm  operator+ (const vecn_tm& o)const{return vecn_tm(x() + o.x(), y() + o.y(), z() + o.z());}
    vecn_tm  operator- (const vecn_tm& o)const{return vecn_tm(x() - o.x(), y() - o.y(), z() - o.z());}
    vecn_tm& operator+=(const vecn_tm& o){*this = *this + o;return *this;}
    vecn_tm& operator-=(const vecn_tm& o){*this = *this - o;return *this;}
    vecn_tm  operator*(const Scalar& o)const{return vecn_tm(x() * o,y() * o, z() * o);}
    vecn_tm  operator/(const Scalar& o)const{return vecn_tm(x() / o,y() / o, z() / o);}
    template<typename stream_t, typename scalar, size_t n>
    friend stream_t& operator<<(stream_t& str, const vecn_tm<scalar, n>& v){
        for(int i = 0;i < n;i++){
            str << v(i) << "\n";
        }
        return str;
    }
};
#endif