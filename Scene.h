//
// Created by roundedglint585 on 1/20/21.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "thirdParty/Vec3.h"
#include "Camera.h"
#include "Mesh.h"

class Scene {
public:
    Scene() = default;

    const Camera &getCamera() const;

    const std::vector<Mesh> &getMeshes() const;
    void addMesh(const Mesh& mesh);
private:
    std::vector<Mesh> meshes_m;
    Camera camera_m;
};


#endif //RAYTRACER_SCENE_H
