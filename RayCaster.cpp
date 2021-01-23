//
// Created by roundedglint585 on 1/23/21.
//

#include "RayCaster.h"

void RayCaster::render(const Scene &scene, Image &image) const {
    image.fillBackgroundWithGradient({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f});
    const Camera &camera = scene.getCamera();
    for (size_t i = 0; i < image.height(); i++) {
        #pragma omp parallel for default(none) shared(image, camera, scene, i)
        for (size_t j = 0; j < image.width(); j++) {
            auto ray = camera.castRay(static_cast<float>(j) / image.width(), static_cast<float>(i) / image.height());
            if(auto intersection = findRayIntersection(scene.getMeshes(), ray)){
                image(i, j) = shade(scene, intersection.value());
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
                    result.u = u;
                    result.v = v;
                    result.t = t;
                    result.triangleIndex = i;
                    result.meshIndex = meshIndex;
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
    const auto& mesh = scene.getMeshes()[intersectionData.meshIndex];
    const auto& vertices = mesh.getVertices();
    const auto& N = mesh.getNormals();
    auto &[p0, p1, p2] = mesh.getIndices()[intersectionData.triangleIndex];
    Vec3<float> hitNormal = normalize((1.f - intersectionData.u - intersectionData.v) * vertices[p0] + intersectionData.u * vertices[p1] + intersectionData.v * vertices[p2]);
    return Vec3f(0.5f, 0.5f, 0.5f) + hitNormal / 2.f;

}
