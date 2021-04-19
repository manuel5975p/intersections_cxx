#ifndef AABB_AABB_HPP
#define AABB_AABB_HPP
#include "structs.hpp"
bool intersect(const aabb& b1, const aabb& b2){
    char overlap[3] = {0};
    for(int i = 0;i < 3;i++){
        overlap[i] = (b1.end(0) > b2.start(0)) | (b1.start(0) < b2.end(0));
    }
    return overlap[0] & overlap[1] & overlap[2];
}
#endif