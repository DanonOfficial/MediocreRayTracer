//
// Created by roundedglint585 on 1/23/21.
//

#include "RayCaster.h"

void RayCaster::render(const Scene &scene, Image &image, size_t sampleCountPerPixel) {
    image.fillBackgroundWithGradient({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f});
    const Camera &camera = scene.getCamera();
    for (size_t i = 0; i < image.height(); i++) {
        #pragma omp parallel for default(none) shared(image, camera, scene, i, gen, sampleCountPerPixel)
        for (size_t j = 0; j < image.width(); j++) {
            if(auto color = samplePixel(scene, image, i, j, sampleCountPerPixel)){
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

Vec3<float> RayCaster::shade(const Scene &scene, RayCaster::IntersectionData intersectionData) const {
    auto &[meshIndex, triangleIndex, u, v, _] = intersectionData;
    const auto& mesh = scene.getMeshes()[meshIndex];
    const auto& vertices = mesh.getVertices();
    const auto& normals = mesh.getNormals();
    auto &[p0, p1, p2] = mesh.getIndices()[triangleIndex];
    Vec3<float> hitNormal = normalize((1.f - u - v) * normals[p0] + u * normals[p1] + v * normals[p2]);
    Vec3<float> hitPos = (1.f - u - v) * vertices[p0] + u * vertices[p1] + v * vertices[p2];
    Vec3<float> resultColor = {0.f, 0.f, 0.f};
    for(auto& lightSource: scene.getLightSources()){
        Vec3<float> lightSourceDirection = normalize(hitPos - lightSource.getPosition());
        Ray ray(lightSource.getPosition(), lightSourceDirection);
        auto intersectionFromLight = findRayIntersection(scene.getMeshes(), ray).value();
        if(intersectionFromLight.meshIndex == intersectionData.meshIndex && intersectionFromLight.triangleIndex == intersectionData.triangleIndex) {
            Vec3<float> colorResponse = mesh.getMaterial().evaluateColorResponse(hitNormal, lightSourceDirection);
            resultColor += colorResponse * lightSource.getIntensity();
        }
    }
    return resultColor;
}

std::optional<Vec3<float>> RayCaster::samplePixel(const Scene &scene, const Image &image, size_t i, size_t j, size_t sampleCount) {
        float fromX, toX, fromY, toY;
        fromX = static_cast<float>(j) / image.width();
        toX = static_cast<float>(j + 1) / image.width();
        fromY = 1.f - static_cast<float>(i) / image.height();
        toY = 1.f - static_cast<float>(i + 1) / image.height();
        std::uniform_real_distribution<> disX(fromX, toX);
        std::uniform_real_distribution<> disY(fromY, toY);
        Vec3<float> color = {0.f, 0.f, 0.f};
        bool isThereAnyIntersection = false;
        for (size_t k = 0; k < sampleCount; k++) {
            auto ray = scene.getCamera().castRay(disX(gen), disY(gen));
            if (auto intersection = findRayIntersection(scene.getMeshes(), ray)) {
                isThereAnyIntersection = true;
                color += shade(scene, intersection.value());
            }
        }
        if(isThereAnyIntersection){
            return {color / 16.f};
        }else{
            return std::nullopt;
        }
}


