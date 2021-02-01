//
// Created by roundedglint585 on 1/31/21.
//

#include "../include/BVH.h"

BVH::treeNode::treeNode(const std::vector<triangleData> &objects, const AABB &aabb): objects(objects), aabb(aabb){
}


std::vector<std::unique_ptr<BVH::treeNode>> BVH::merge(std::vector<std::unique_ptr<BVH::treeNode>> &&nodes) {
    //down-up building strategy
    std::vector<uint8_t> isUnited(nodes.size(), false);
    std::vector<std::unique_ptr<BVH::treeNode>> result;
    size_t nodesCountToProceed = nodes.size();
    if(nodesCountToProceed % 2 == 1) { // if there non even count of nodes, last one goes to the next level
        nodesCountToProceed--;
        isUnited.pop_back();
        result.push_back(std::move(nodes.back()));
    }
    for(size_t i = 0; i < nodesCountToProceed; i++){ //by design should be zero with modulo 2
        if(isUnited[i]){
            continue;
        }
        int minVolumeIndex;
        float minVolume = std::numeric_limits<float>::max();
        isUnited[i] = true;
        for(size_t j = 0; j < nodesCountToProceed; j++){
            if(i == j || isUnited[j]){
                continue;
            }
            float unitedVolume = nodes[i]->aabb.combine(nodes[j]->aabb).getVolume();
            if(unitedVolume < minVolume){
                minVolume = unitedVolume;
                minVolumeIndex = j;
            }
        }
        std::vector<triangleData> mergedData = nodes[i]->objects;
        mergedData.insert( mergedData.end(), nodes[minVolumeIndex]->objects.begin(), nodes[minVolumeIndex]->objects.end());
        std::unique_ptr<BVH::treeNode> mergedNode = std::make_unique<BVH::treeNode>(mergedData, nodes[i]->aabb.combine(nodes[minVolumeIndex]->aabb));
        mergedNode->left = std::move(nodes[i]);
        mergedNode->right = std::move(nodes[minVolumeIndex]);
        result.push_back(std::move(mergedNode));
        isUnited[minVolumeIndex] = true;
    }
    return result;
}

void BVH::buildTree(const std::vector<Mesh> &meshes) {
    std::vector<std::unique_ptr<BVH::treeNode>> allTriangles;
    for(size_t meshIndex = 0; meshIndex < meshes.size(); meshIndex++){
        auto mesh = meshes[meshIndex];
        for(size_t triangleIndex = 0; triangleIndex < mesh.getIndices().size(); triangleIndex++){
            std::vector<Vec3<float>> vertices(3);
            for(size_t i = 0; i < 3; i++){
                vertices[i] = mesh.getVertices()[mesh.getIndices()[triangleIndex][i]];
            }
            AABB aabb(vertices);
            triangleData data = {meshIndex, triangleIndex};
            std::vector<triangleData> triangles = {data};
            std::unique_ptr<BVH::treeNode> node = std::make_unique<BVH::treeNode>(triangles, aabb);
            allTriangles.push_back(std::move(node));
        }
    }
    while(allTriangles.size() != 1){
        allTriangles = merge(std::move(allTriangles));
    }
    root_m = std::move(allTriangles[0]);
}


std::vector<BVH::triangleData> BVH::getIntersection(const Ray &ray) const {
    std::vector<BVH::triangleData> result;
    if(root_m->aabb.rayIntersect(ray)) {
        getIntersection(ray, root_m, result);
    }
    return result;
}

void BVH::getIntersection(const Ray &ray, const std::unique_ptr<treeNode> &node,
                          std::vector<triangleData> &intersections) const {
    if(node->left == nullptr && node->right == nullptr){
        intersections.insert(intersections.end(), node->objects.begin(), node->objects.end());
    }
    if(node->left != nullptr && node->left->aabb.rayIntersect(ray)){
        getIntersection(ray, node->left, intersections);
    }
    if(node->right != nullptr && node->right->aabb.rayIntersect(ray)){
        getIntersection(ray, node->right, intersections);
    }
}

BVH::BVH(const std::vector<Mesh> &meshes) {
    buildTree(meshes);
}




