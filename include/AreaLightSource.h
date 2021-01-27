//
// Created by roundedglint585 on 1/27/21.
//

#ifndef RAYTRACER_AREALIGHTSOURCE_H
#define RAYTRACER_AREALIGHTSOURCE_H

#include "LightSource.h"

class AreaLightSource: public LightSource {
public:
    //LightSource(const Vec3<float> &position, const Vec3<float> &color, float intensity);
    // Square for now
    AreaLightSource(const Vec3<float> &position, const Vec3<float> &direction, const Vec3<float> &color, float intensity, float squareSize);

    const Vec3<float> getPosition() const override;
private:
    Vec3<float> firstBasisVector_m, secondBasisVector_m;
    Vec3<float> lookAt_m;
    float squareSize_m;
};


#endif //RAYTRACER_AREALIGHTSOURCE_H
