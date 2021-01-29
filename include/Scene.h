//
// Created by roundedglint585 on 1/20/21.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "../thirdParty/Vec3.h"
#include "Camera.h"
#include "Mesh.h"
#include "LightSource.h"
#include "AreaLightSource.h"

class Scene {
public:
    Scene() = default;

    const Camera &getCamera() const;

    const std::vector<Mesh> &getMeshes() const;

    const std::vector<AreaLightSource> &getLightSources() const;

    void addMesh(const Mesh &mesh);

    void addLightSource(const AreaLightSource &lightSource);

private:
    std::vector<Mesh> meshes_m;
    std::vector<AreaLightSource> lightSources_m;
    Camera camera_m;
};


#endif //RAYTRACER_SCENE_H
