//
// Created by roundedglint585 on 1/27/21.
//

#include "../include/AreaLightSource.h"
#include "../include/Random.h"

AreaLightSource::AreaLightSource(const Vec3<float> &position, const Vec3<float> &lookAt, const Vec3<float> &color,
                                 float intensity,
                                 float squareSize) : LightSource(position, color, intensity), lookAt_m(lookAt),
                                                     squareSize_m(squareSize) {
    firstBasisVector_m = cross({0.f, 0.f, 1.f}, lookAt_m - position_m);
    secondBasisVector_m = cross({0.f, 1.f, 0.f}, lookAt_m - position_m);
}


const Vec3<float> AreaLightSource::getPosition() const {
    Vec3<float> pos = position_m;
    firstBasisVector.normalize();
    secondBasisVector.normalize();
    pos += randomGenerator::floatRandom(-1.f, 1.f) * squareSize_m / 2.f * firstBasisVector;
    pos += randomGenerator::floatRandom(-1.f, 1.f) * squareSize_m / 2.f * secondBasisVector;
    return pos;
}

