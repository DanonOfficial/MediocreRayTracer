//
// Created by roundedglint585 on 1/20/21.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <vector>
#include "thirdParty/Vec3.h"
#include "Camera.h"
class Scene {
public:
    Scene() = default;
    Scene(const std::vector<Vec3<float>> &vertices, const std::vector<Vec3<size_t>> &triangles);

private:
    std::vector<Vec3<float>> vertices_m;
    std::vector<Vec3<size_t>> triangles_m;
public:
    const std::vector<Vec3<float>> &getVertices() const;

    const std::vector<Vec3<size_t>> &getTriangles() const;

    const Camera &getCamera() const;

private:

    Camera camera_m;
};


#endif //RAYTRACER_SCENE_H
