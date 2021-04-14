#include "intersections.hpp"
#include <iostream>
#include <numeric>
#include <chrono>
#include <vector>
unsigned long long nanoTime(){
    using namespace std;
    using namespace chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}
template<size_t run_length = 300, typename Function, typename... Ts>
double bench_function(Function f, Ts&&... args){
    unsigned int since_best = 0;
    unsigned long long best_time = -1;
    unsigned long long accum = 0;
    while(true){
        auto t1 = std::nanoTime();
        f(std::forward<Ts>(args)...);
        auto t2 = std::nanoTime();
        if(t2 - t1 < best_time){
            best_time = t2 - t1;
            since_best = 0;
            accum = 0;
            accum += (t2 - t1);
        }
        else{
            since_best++;
            accum += (t2 - t1);
        }
        if(since_best >= run_length){
            break;
        }
    }
    return accum / double(run_length);
}

int main(){
    ray r     {vec3(0,0,0), vec3(1, 0, 0)};
    triangle t{vec3(1,-1,-1), vec3(1,2,0), vec3(1,-1,1)};
    sphere s  {vec3(1,0,0), 0.5};
    aabb b    {vec3(3,-1,-1), vec3(4,2,2)};
    double time = bench_function<3000>([&]{
        int accum = 0;
        for(size_t i = 0;i < 100000;i++){
            accum += intersect(r, b).has_value();
            r.o(0) -= 0.01;
        }
        if(accum == 100){
            std::terminate();
        }
    });
    std::cout << time << " ns\n";
}
