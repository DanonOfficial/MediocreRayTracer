//
// Created by roundedglint585 on 1/23/21.
//

#include "Mesh.h"
#include <fstream>
void Mesh::loadOFF(const std::string &path) {
    std::ifstream file(path);
    std::string mark;
    size_t indicesCount, verticesCount, edgesCount;
    if(file){
        file >> mark;
        if(mark != "OFF"){
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
    }
}

void Mesh::calculateNormals() {
    if(indices_m.size() != normals_m.size()){
        normals_m.resize(indices_m.size());
    }
    for(size_t i = 0; i < normals_m.size(); i++){
        const auto &[i0, i1, i2] = indices_m[i];
        normals_m[i] = normalize(cross(vertices_m[i1] - vertices_m[i0], vertices_m[i2] - vertices_m[i0]));
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
