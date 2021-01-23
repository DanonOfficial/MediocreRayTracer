//
// Created by roundedglint585 on 1/20/21.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <vector>
#include "thirdParty/Vec3.h"

class Scene {
public:
    Scene() = default;
    Scene(const std::vector<Vec3<float>> &vertices, const std::vector<Vec3<size_t>> &triangles);

private:
    std::vector<Vec3<float>> vertices_m;
    std::vector<Vec3<size_t>> triangles_m;

    Vec3<float> cameraPos_m = {0.f, 0.f, 0.f};
    Vec3<float> cameraDirection_m = {0.f, 0.f, -1.f};
    float fow_m = 45.f;
    float aspectRation_m = 3.f / 2.f;
};


#endif //RAYTRACER_SCENE_H
