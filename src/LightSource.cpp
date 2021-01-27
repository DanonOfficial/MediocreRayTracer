//
// Created by roundedglint585 on 1/26/21.
//

#include "../include/LightSource.h"

LightSource::LightSource(const Vec3<float> &position, const Vec3<float> &color, float intensity) : position_m(
        position), color_m(color), intensity_m(intensity) {}

Vec3<float> LightSource::getPosition() const {
    return position_m;
}

const Vec3<float> LightSource::getColor() const {
    return color_m;
}

float LightSource::getIntensity() const {
    return intensity_m;
}
