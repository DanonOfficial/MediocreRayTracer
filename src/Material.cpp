//
// Created by roundedglint585 on 1/26/21.
//

#include "../include/Material.h"

Material::Material(const Vec3<float> &albedo, float diffuseCoeff, float roughness, const Vec3<float> &refractionIndex)
        : albedo_m(albedo),
          diffuseCoeff_m(diffuseCoeff), roughness_m(roughness), refractionIndex_m(refractionIndex) {}

Vec3<float> Material::evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi) const {
    // expect that normal and wi normalized already
    return albedo_m * std::abs(dot(normal, wi)); //without intensity
}

Vec3<float>
Material::evaluateColorResponse(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const {
    auto con = (specularD(normal, wi, wo) * specularF(wi, wo) * specularG(normal, wi, wo) /
                        (4 * dot(normal, wi) * dot(normal, wo)));
    return albedo_m * con + albedo_m * diffuseCoeff_m / M_PI;
}

float Material::specularD(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const {
    float roughnessSquared = roughness_m * roughness_m;
    Vec3<float> halfVector = calculateHalfVector(wi, wo);
    return static_cast<float>(roughnessSquared /
                              (M_PI * std::pow(1 + (roughnessSquared - 1) * std::pow(dot(normal, halfVector), 2), 2)));
}

Vec3<float> Material::calculateHalfVector(const Vec3<float> &wi, const Vec3<float> &wo) const {
    return (wi + wo) / (wi + wo).length();
}

float Material::specularF(const Vec3<float> &wi, const Vec3<float> &wo) const {
    return refractionIndex_m[0] + (1 - refractionIndex_m[0]) * std::pow(1 - std::max(0.f, dot(wi, wo)), 5);
}

float Material::specularG(const Vec3<float> &normal, const Vec3<float> &wi, const Vec3<float> &wo) const {
    float k = std::pow(roughness_m + 1, 2) / 8.f;
    auto g1 = [normal, k](const Vec3<float> &w) {
        return dot(normal, w) / (dot(normal, w) * (1 - k) + k);
    };
    return g1(wi) * g1(wo);
}

