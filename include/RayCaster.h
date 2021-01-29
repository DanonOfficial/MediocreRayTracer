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
    void render(const Scene &scene, Image &image,
                size_t sampleCountPerPixel = 8) const; //changing state of the random generator

private:
    struct IntersectionData {
        size_t meshIndex;
        size_t triangleIndex;
        float u;
        float v;
        float t;
    };

    std::optional<Vec3<float>>
    sampleCameraPixel(const Scene &scene, const Image &image, size_t i, size_t j, size_t sampleCount = 8) const;

    Vec3<float> sampleShadowColor(const Scene &scene, const LightSource &lightSource, const Vec3<float> &hitPos,
                                  const Vec3<float> &hitNormal, const Vec3<float> &rayDirection, size_t meshIndex, size_t triangleIndex,
                                  size_t sampleCount = 8) const;

    std::optional<IntersectionData> findRayIntersection(const std::vector<Mesh> &meshes, const Ray &ray) const;

    Vec3<float> shade(const Scene &scene, const Ray &ray, IntersectionData intersectionData, size_t sampleCount = 8) const;
};


#endif //RAYTRACER_RAYCASTER_H
