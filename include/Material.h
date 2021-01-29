//
// Created by roundedglint585 on 1/26/21.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "../thirdParty/Vec3.h"

class Material {
public:
    Material() = default;

    Material(const Vec3<float> &albedo, float diffuseCoeff, float roughness_m, const Vec3<float> &refractionIndex);

    Vec3<float> evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi) const;

    Vec3<float> evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const;

private:

    float specularD(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const;
    float specularF(const Vec3<float> &wi, const Vec3<float> &wo) const;
    float specularG(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const;

    Vec3<float> calculateHalfVector(const Vec3<float> &wi, const Vec3<float> &wo) const;
    Vec3<float> albedo_m = {};
    float diffuseCoeff_m = 0.f;
    float roughness_m = 0.5f;
    Vec3<float> refractionIndex_m = {0.05f, 0.05f, 0.05f};
};


#endif //RAYTRACER_MATERIAL_H
