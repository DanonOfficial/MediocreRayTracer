//
// Created by roundedglint585 on 1/30/21.
//

#include "../include/AABB.h"


bool AABB::rayIntersect(const Ray &ray) const {

    float invD = 1.f / ray.getDirection()[0];
    float tmin = ((ray.getDirection()[0] < 0 ? max[0] : min[0]) - ray.getOrigin()[0]) * invD;
    float tmax = ((ray.getDirection()[0] < 0 ? min[0] : max[0]) - ray.getOrigin()[0]) * invD;

    for(size_t i = 0; i < 3; i++){
        invD = 1.f / ray.getDirection()[i];
        float t0 = (min[i] - ray.getOrigin()[i]) * invD;
        float t1 = (max[i] - ray.getOrigin()[i]) * invD;
        if(invD < 0.f){
            std::swap(t0, t1);
        }
        tmin = std::max(t0, tmin);
        tmax = std::min(t1, tmax);
        if(tmax <= tmin){
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

float AABB::getVolume() const {
    Vec3<float> sides = max - min;
    return std::abs(sides[0] * sides[1] * sides[2]);
}

AABB AABB::combine(const AABB &aabb) const {
    Vec3<float> resultMin;
    Vec3<float> resultMax;
    for(size_t i = 0; i < 3; i++){
        resultMin[i] = std::min(min[i], aabb.min[i]);
        resultMax[i] = std::max(max[i], aabb.max[i]);
    }
    return {resultMin, resultMax};
}

AABB::AABB(const Vec3<float> &min, const Vec3<float> &max) :min(min), max(max) {

}

Vec3<float> AABB::middle() const {
    return (min + max) / 2.f;
}
