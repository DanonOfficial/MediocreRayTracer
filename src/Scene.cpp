//
// Created by roundedglint585 on 1/20/21.
//

#include "../include/Scene.h"
#include "../include/AreaLightSource.h"

const Camera &Scene::getCamera() const {
    return camera_m;
}

const std::vector<Mesh> &Scene::getMeshes() const {
    return meshes_m;
}

void Scene::addMesh(const Mesh &mesh) {
    meshes_m.push_back(mesh);
    auto &value = *this;
}

const std::vector<AreaLightSource> &Scene::getLightSources() const {
    return lightSources_m;
}

void Scene::addLightSource(const AreaLightSource &lightSource) {
    lightSources_m.emplace_back(lightSource);
}

void Scene::buildBVH() {
    bvh = BVH(meshes_m);

}

const BVH &Scene::getBVH() const {
    return bvh;
}

