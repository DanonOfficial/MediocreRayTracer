//
// Created by roundedglint585 on 1/20/21.
//

#include "Scene.h"



const Camera &Scene::getCamera() const {
    return camera_m;
}

const std::vector<Mesh> &Scene::getMeshes() const {
    return meshes_m;
}

void Scene::addMesh(const Mesh &mesh) {
    meshes_m.push_back(mesh);
}
