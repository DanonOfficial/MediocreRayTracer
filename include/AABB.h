//
// Created by roundedglint585 on 1/30/21.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "Ray.h"
#include <vector>

class AABB {
public:
    AABB() = default;
    explicit AABB(const std::vector<Vec3<float>> &vertices);
    AABB(const Vec3<float> &min, const Vec3<float> &max);
    bool rayIntersect(const Ray &ray) const;
    float getVolume() const;
    AABB combine(const AABB &aabb) const;
private:
    Vec3<float> min, max;
};


#endif //RAYTRACER_AABB_H
