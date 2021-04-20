#intersections_cxx
#### A fast C++17 header-only primitive-primitive intersection library
|        |ray|triangle|sphere|cylinder|AABB|
|---|---|---|---|---|---|
|ray     | ❌ | ✅   | ✅ | ✅ | ✅ |
|triangle| ✅ | ✅   | ❌ | ❌ | ✅ |
|sphere  | ✅ | ❌   | ✅ | ❌ | ❌ |
|cylinder| ✅ | ❌   | ❌ | ❌ | ❌ |
|AABB    | ✅ | ✅   | ✅ | ❌ | ✅ |

#####Usage Example:
```cpp
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
```
**Caution:** u and v are only correctly set for ray-triangle intersections.
#####Another example
```cpp
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
```
