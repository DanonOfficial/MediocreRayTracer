//
// Created by roundedglint585 on 1/23/21.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <vector>
#include "../thirdParty/Vec3.h"
#include "Material.h"

class Mesh {
public:
    Mesh() = default;

    void loadOFF(const std::string &path);

    const std::vector<Vec3<float>> &getVertices() const;

    const std::vector<Vec3<size_t>> &getIndices() const;

    const std::vector<Vec3<float>> &getNormals() const;

    const Material &getMaterial() const;

    void setMaterial(const Material &material);

private:
    std::vector<Vec3<float>> vertices_m;
    std::vector<Vec3<size_t>> indices_m;
    std::vector<Vec3<float>> normals_m;
    Material material_m;

    void calculateNormals();
};


#endif //RAYTRACER_MESH_H
