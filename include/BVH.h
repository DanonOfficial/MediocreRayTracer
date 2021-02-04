//
// Created by roundedglint585 on 1/31/21.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include <vector>
#include "Mesh.h"
#include "Ray.h"
#include <memory>

class BVH {
public:
    BVH() = default;

    BVH(const std::vector<Mesh> &meshes);

    struct triangleData {
        size_t meshIndex, triangleIndex;
    };

    std::vector<triangleData> getIntersection(const Ray &ray) const;

private:

    struct treeNode {
        treeNode(const std::vector<triangleData> &objects, const AABB &aabb);

        AABB aabb;
        std::vector<triangleData> objects;
        std::unique_ptr<treeNode> left = nullptr;
        std::unique_ptr<treeNode> right = nullptr;
    };

    void buildTree(const std::vector<Mesh> &meshes);

    std::vector<std::unique_ptr<BVH::treeNode>> merge(std::vector<std::unique_ptr<treeNode>> &&nodes);

    void getIntersection(const Ray &ray, const std::unique_ptr<treeNode> &node,
                         std::vector<triangleData> &intersections) const;

    std::unique_ptr<treeNode> root_m;
};


#endif //RAYTRACER_BVH_H
