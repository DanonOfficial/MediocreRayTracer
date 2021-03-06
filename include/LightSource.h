//
// Created by roundedglint585 on 1/26/21.
//

#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "../thirdParty/Vec3.h"

class LightSource {
public:
    LightSource(const Vec3<float> &position, const Vec3<float> &color, float intensity);

    virtual ~LightSource() = default;

    virtual Vec3<float> getPosition() const;

    const Vec3<float> getColor() const;

    float getIntensity() const;

protected:
    Vec3<float> position_m, color_m;
    float intensity_m;
};


#endif //RAYTRACER_LIGHTSOURCE_H
