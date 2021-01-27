//
// Created by roundedglint585 on 1/26/21.
//

#include "../include/Material.h"

Material::Material(const Vec3<float> &albedo, float diffuseCoeff) : albedo_m(albedo),
                                                                    diffuseCoeff_m(diffuseCoeff) {}

Vec3<float> Material::evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi) const {
    // expect that normal and wi normalized already
    return albedo_m * std::abs(dot(normal, wi)); //without intensity
}
