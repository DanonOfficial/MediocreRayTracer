//
// Created by roundedglint585 on 1/23/21.
//

#ifndef RAYTRACER_RAYCASTER_H
#define RAYTRACER_RAYCASTER_H


#include "Image.h"
#include "Scene.h"

class RayCaster {
public:
    void render(const Scene &scene, Image &image) const;

private:
    struct IntersectionData {
        size_t meshIndex;
        size_t triangleIndex;
        float u;
        float v;
        float t;
    };
    std::optional<IntersectionData> findRayIntersection(const std::vector<Mesh> &meshes, const Ray &ray) const;
    Vec3<float> shade(const Scene &scene, IntersectionData intersectionData) const;
};


#endif //RAYTRACER_RAYCASTER_H
