//
// Created by roundedglint585 on 1/23/21.
//

#ifndef RAYTRACER_RAYCASTER_H
#define RAYTRACER_RAYCASTER_H


#include "Image.h"
#include "Scene.h"
#include <random>
class RayCaster {
public:
    void render(const Scene &scene, Image &image, size_t sampleCountPerPixel = 8); //changing state of the random generator

private:
    struct IntersectionData {
        size_t meshIndex;
        size_t triangleIndex;
        float u;
        float v;
        float t;
    };
    std::optional<Vec3<float>> samplePixel(const Scene &scene, const Image &image, size_t i, size_t j, size_t sampleCount = 8);
    std::optional<IntersectionData> findRayIntersection(const std::vector<Mesh> &meshes, const Ray &ray) const;
    Vec3<float> shade(const Scene &scene, IntersectionData intersectionData) const;
    std::random_device rd{};  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen = std::mt19937 (rd());
};


#endif //RAYTRACER_RAYCASTER_H
