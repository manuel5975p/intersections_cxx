#include <intersections.hpp>
#include <iostream>
int main(){
    ray<float> r(vec3f(0, 0, 0),  //Construct a ray with
                 vec3f(0, 0, 1)); //origo and direction
    //Btw, vec3f = vec3_tm<float>
    triangle<float> t(vec3f(-1, -1, 1),  
                      vec3f( 0,  1, 1),  //Construct a triangle
                      vec3f( 1, -1, 1)); //with three vertices

    std::optional<intersection<float>> ints_opt = intersect(r, t);

    if(ints_opt.has_value()){
        intersection<float> ints = ints_opt.value();
        std::cout << ints.p << " Intersection point\n";
        std::cout << ints.t << " Direction multiple to p\n";
        std::cout << ints.u << " U coordinate on hit triangle\n";
        std::cout << ints.v << " V coordinate on hit triangle\n";
    }
}