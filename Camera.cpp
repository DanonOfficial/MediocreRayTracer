////
//// Created by roundedglint585 on 1/23/21.
////
//
#include "Camera.h"

Camera::Camera(const Vec3<float> &pos, const Vec3<float> &lookAt, const Vec3<float> &up, float aspectRatio,
               float fov) : pos_m(pos), lookAt_m(lookAt), up_m(up), aspectRatio_m(aspectRatio), fov_m(fov) {
    float distanceFromCameraToScreen = length(lookAt_m - up_m);
    float povInRadian = fov_m * static_cast<float>(M_PI) / 180.f;
    float halfHeight = tanf(povInRadian / 2.f) * distanceFromCameraToScreen;
    float halfWidth = halfHeight * aspectRatio_m;
    u_m = cross(lookAt_m - pos_m, up);
    normalize(u_m);
    u_m = 2.f * halfWidth * u_m;
    v_m = cross(lookAt_m - pos_m, u_m);
    normalize(v_m);
    v_m = 2.f * halfWidth * v_m;
    leftCorner_m = pos_m - halfWidth * u_m - halfHeight * v_m - normalize(lookAt_m - pos_m);
}

Ray Camera::castRay(float u, float v) const {
    return Ray(pos_m, normalize(leftCorner_m + u * u_m + v * v_m - pos_m));
}
