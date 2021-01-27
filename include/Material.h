//
// Created by roundedglint585 on 1/26/21.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include "../thirdParty/Vec3.h"

class Material {
public:
    Material() = default;
    Material(const Vec3<float> &albedo, float diffuseCoeff);
    Vec3<float> evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi) const;

private:
    Vec3<float> albedo_m = {};
    float diffuseCoeff_m = 0.f;
};


#endif //RAYTRACER_MATERIAL_H
