//
// Created by roundedglint585 on 1/23/21.
//

#include "../include/RayCaster.h"
#include "../include/Random.h"

void RayCaster::render(const Scene &scene, Image &image, size_t sampleCountPerPixel) const {
    image.fillBackgroundWithGradient({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f});
    const Camera &camera = scene.getCamera();
#pragma omp parallel for default(none) shared(image, camera, scene, sampleCountPerPixel)
    for (size_t i = 0; i < image.height(); i++) {
        for (size_t j = 0; j < image.width(); j++) {
            if (auto color = sampleCameraPixel(scene, image, i, j, sampleCountPerPixel)) {
                image(j, i) = color.value();
            }
        }
    }
}

std::optional<RayCaster::IntersectionData>
RayCaster::findRayIntersection(const std::vector<Mesh> &meshes, const Ray &ray) const {
    float distance = std::numeric_limits<float>::max();
    RayCaster::IntersectionData result{};
    bool hasIntersection = false;
    for (size_t meshIndex = 0; meshIndex < meshes.size(); meshIndex++) {
        const std::vector<Vec3<size_t>> &indices = meshes[meshIndex].getIndices();
        const std::vector<Vec3<float>> &vertices = meshes[meshIndex].getVertices();
        for (size_t i = 0; i < indices.size(); i++) {
            auto &[i0, i1, i2] = indices[i];
            if (auto intersection = ray.intersect(vertices[i0], vertices[i1], vertices[i2])) {
                const auto &[u, v, t] = intersection.value();
                if (std::fabs(t) < distance) {
                    hasIntersection = true;
                    distance = std::fabs(t);
                    result = {meshIndex, i, u, v, t};
                }
            }
        }
    }
    if (!hasIntersection) {
        return std::nullopt;
    } else {
        return {result};
    }
}

Vec3<float>
RayCaster::shade(const Scene &scene, const Ray &ray, RayCaster::IntersectionData intersectionData, size_t sampleCount) const {
    auto &[meshIndex, triangleIndex, u, v, _] = intersectionData;
    const auto &mesh = scene.getMeshes()[meshIndex];
    const auto &vertices = mesh.getVertices();
    const auto &normals = mesh.getNormals();
    auto &[p0, p1, p2] = mesh.getIndices()[triangleIndex];
    Vec3<float> hitNormal = normalize((1.f - u - v) * normals[p0] + u * normals[p1] + v * normals[p2]);
    Vec3<float> hitPos = (1.f - u - v) * vertices[p0] + u * vertices[p1] + v * vertices[p2];
    Vec3<float> resultColor = {0.f, 0.f, 0.f};
    for (auto &lightSource: scene.getLightSources()) {
        resultColor += sampleShadowColor(scene, lightSource, hitPos, hitNormal, ray.getDirection(), meshIndex, triangleIndex, sampleCount);
    }
    return resultColor;
}

std::optional<Vec3<float>>
RayCaster::sampleCameraPixel(const Scene &scene, const Image &image, size_t i, size_t j, size_t sampleCount) const {
    float fromX, toX, fromY, toY;
    fromX = static_cast<float>(j) / image.width();
    toX = static_cast<float>(j + 1) / image.width();
    fromY = 1.f - static_cast<float>(i) / image.height();
    toY = 1.f - static_cast<float>(i + 1) / image.height();
    Vec3<float> color = {0.f, 0.f, 0.f};
    bool isThereAnyIntersection = false;
    for (size_t k = 0; k < sampleCount; k++) {
        auto ray = scene.getCamera().castRay(randomGenerator::floatRandom(fromX, toX),
                                             randomGenerator::floatRandom(fromY, toY));
        if (auto intersection = findRayIntersection(scene.getMeshes(), ray)) {
            isThereAnyIntersection = true;
            color += shade(scene, ray, intersection.value());
        }
    }
    if (isThereAnyIntersection) {
        return {color / static_cast<float>(sampleCount)};
    } else {
        return std::nullopt;
    }
}

Vec3<float> RayCaster::sampleShadowColor(const Scene &scene, const LightSource &lightSource, const Vec3<float> &hitPos,
                                         const Vec3<float> &hitNormal, const Vec3<float> &rayDirection, size_t meshIndex, size_t triangleIndex,
                                         size_t sampleCount) const {
    Vec3<float> resultColor = {0.f, 0.f, 0.f};
    for (size_t i = 0; i < sampleCount; i++) {
        auto lightPosition = lightSource.getPosition();
        Vec3<float> lightSourceDirection = normalize(hitPos - lightPosition);
        Ray ray(lightPosition, lightSourceDirection);
        if (auto intersectionFromLight = findRayIntersection(scene.getMeshes(), ray)) {
            if (intersectionFromLight.value().meshIndex == meshIndex &&
                intersectionFromLight.value().triangleIndex == triangleIndex) {
                Vec3<float> colorResponse = scene.getMeshes()[meshIndex].getMaterial().evaluateColorResponse(hitNormal,
                                                                                                             lightSourceDirection,
                                                                                                             rayDirection);
                resultColor += colorResponse * lightSource.getIntensity();
            }
        }
    }
    resultColor = resultColor / sampleCount;
    return resultColor;
}


