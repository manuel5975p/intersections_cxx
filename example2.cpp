#include <intersections.hpp>
#include <iostream>
int main(){
    ray<float> r(vec3f(0, 0, 0),
                 vec3f(0, 0, 1));
    aabb<float> b(vec3f(-1, -1, 1), //Construct aabb using
                  vec3f( 1,  1, 2));//minima and maxima in each dimension

    
    std::optional<double_intersection<float>> dints_opt = intersect(r, b);

    //A ray can intersect twice with an aabb. Therefore the result is a double_intersection.
    if(dints_opt.has_value()){
        double_intersection<float> dints = dints_opt.value();
        std::cout << dints.p.first  << " First intersection point\n";
        std::cout << dints.p.second << " Second intersection point\n";

        std::cout << dints.t.first  << " First intersection t\n";
        std::cout << dints.t.second << " Second intersection t\n";
    }
}