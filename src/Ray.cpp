//
// Created by roundedglint585 on 1/20/21.
//

#include "../include/Ray.h"
#include <optional>
Ray::Ray(const Vec3<float> &originM, const Vec3<float> &directionM) : origin_m(originM), direction_m(directionM) {}

std::optional<Vec3<float>> Ray::intersect(const Vec3<float> &p0, const Vec3<float> &p1, const Vec3<float> &p2) const {
    Vec3<float> e0 = p1 - p0;
    Vec3<float> e1 = p2 - p0;
    Vec3<float> n = cross(direction_m, e1);
    float det = dot(e0, n);
    if(std::fabs(det) <= std::numeric_limits<float>::epsilon()){
        return std::nullopt;
    }

    float invDet = 1 / det;
    Vec3<float> tvec = origin_m - p0;
    float u = dot(tvec, n) * invDet;
    if(u < 0 || u > 1){
        return std::nullopt;
    }

    Vec3<float> qvec = cross(tvec, e0);
    float v = dot(direction_m, qvec) * invDet;
    if(v < 0 || u + v > 1){
        return std::nullopt;
    }
    float t = dot(e1, qvec) * invDet;
    return {{u, v, t}};
}
