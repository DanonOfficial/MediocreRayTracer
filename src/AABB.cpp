//
// Created by roundedglint585 on 1/30/21.
//

#include "../include/AABB.h"

bool AABB::rayIntersect(const Ray &ray) const {

    float tmin, tmax;
    float invD = 1.f / ray.getDirection()[0];
    if(ray.getDirection()[0] < 0) {
        tmin = (max[0] - ray.getOrigin()[0]) * invD;
        tmax = (min[0] - ray.getOrigin()[0]) * invD;
    }else{
        tmin = (min[0] - ray.getOrigin()[0]) * invD;
        tmax = (max[0] - ray.getOrigin()[0]) * invD;
    }
    for(size_t i = 0; i < 3; i++){
        invD = 1.f / ray.getDirection()[i];
        float t0 = (min[i] - ray.getOrigin()[i]) * invD;
        float t1 = (max[i] - ray.getOrigin()[i]) * invD;
        if(invD < 0.f){
            std::swap(t0, t1);
        }
        tmin = std::max(t0, tmin);
        tmax = std::min(t1, tmax);
        if(tmax < tmin){
            return false;
        }
    }
    return true;
}

AABB::AABB(const std::vector<Vec3<float>> &vertices) {
    min = Vec3<float>(std::numeric_limits<float>::max());
    max = Vec3<float>(std::numeric_limits<float>::min());
    for(auto &vertex: vertices){
        for(size_t i = 0; i < 3; i++){
            min[i] = std::min(min[i], vertex[i]);
            max[i] = std::max(max[i], vertex[i]);
        }
    }
}
