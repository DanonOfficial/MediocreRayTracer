//
// Created by roundedglint585 on 1/20/21.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "thirdParty/Vec3.h"
#include <optional>

class Ray {
public:
    Ray(const Vec3<float> &originM, const Vec3<float> &directionM);

    std::optional<Vec3<float>> intersect(const Vec3<float> &p0, const Vec3<float> &p1, const Vec3<float> &p2) const;

private:
    Vec3<float> origin_m;
    Vec3<float> direction_m;
};


#endif //RAYTRACER_RAY_H
