//
// Created by roundedglint585 on 1/23/21.
//

#include "../include/Mesh.h"
#include <fstream>
void Mesh::loadOFF(const std::string &path) {
    std::ifstream file(path);
    std::string mark;
    size_t indicesCount, verticesCount, edgesCount;
    if(file){
        file >> mark;
        if(mark != "OFF"){
            std::cerr << "Wrong file format" << std::endl;
            return;
        }
        file >> verticesCount >> indicesCount >> edgesCount;
        vertices_m.resize(verticesCount);
        indices_m.resize(indicesCount);
        normals_m.resize(indicesCount);
        for(auto &vertex: vertices_m){
            file >> vertex[0] >> vertex[1] >> vertex[2];
        }
        size_t faceIndicesCount;
        for(auto &index: indices_m){
            file >> faceIndicesCount;
            if(faceIndicesCount != 3){
                std::cerr << "Wrong file format" << std::endl;
                return;
            }
            file >> index[0] >> index[1] >> index[2];
        }
        calculateNormals();
    }
}

void Mesh::calculateNormals() {
    normals_m.resize(vertices_m.size(), Vec3f());
    for(auto & i : indices_m){
        const auto &[i0, i1, i2] = i;
        Vec3<float> normal = normalize(cross(vertices_m[i1] - vertices_m[i0], vertices_m[i2] - vertices_m[i0]));
        for(size_t j = 0; j < 3; j++){
            normals_m[i[j]] += normal;
        }
    }
    for(auto & i : normals_m){
        i.normalize();
    }
}

const std::vector<Vec3<float>> &Mesh::getVertices() const {
    return vertices_m;
}

const std::vector<Vec3<size_t>> &Mesh::getIndices() const {
    return indices_m;
}

const std::vector<Vec3<float>> &Mesh::getNormals() const {
    return normals_m;
}

void Mesh::setMaterial(const Material &material) {
    material_m = material;
}

const Material &Mesh::getMaterial() const {
    return material_m;
}
