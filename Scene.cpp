//
// Created by roundedglint585 on 1/20/21.
//

#include "Scene.h"

Scene::Scene(const std::vector<Vec3<float>> &vertices, const std::vector<Vec3<size_t>> &triangles) : vertices_m(vertices), triangles_m(triangles) {

}

const std::vector<Vec3<float>> &Scene::getVertices() const {
    return vertices_m;
}

const std::vector<Vec3<size_t>> &Scene::getTriangles() const {
    return triangles_m;
}

const Camera &Scene::getCamera() const {
    return camera_m;
}
