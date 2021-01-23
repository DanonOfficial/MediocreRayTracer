//
// Created by roundedglint585 on 1/23/21.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#pragma once

#include "thirdParty/Vec3.h"
#include "Ray.h"

class Camera {
public:
    Camera(const Vec3<float> &pos = {0.f, 0.f, 0.f}, const Vec3<float> &lookDirection = {0.f, 0.f, -1.f},
           const Vec3<float> &up = {0.f, 1.f, 0.f}, float aspectRatio = 3.f / 2.f, float fov = 45.f);

    Ray castRay(float u, float v) const;

private:
    Vec3<float> pos_m, lookAt_m, up_m;
    float aspectRatio_m, fov_m;
    Vec3<float> u_m, v_m;
    Vec3<float> leftCorner_m;
};

#endif //RAYTRACER_CAMERA_H
