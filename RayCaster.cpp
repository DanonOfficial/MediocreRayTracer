//
// Created by roundedglint585 on 1/23/21.
//

#include "RayCaster.h"

void RayCaster::render(const Scene &scene, Image &image) const {
    image.fillBackgroundWithGradient({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f});
    const Camera& camera = scene.getCamera();
    const auto& points = scene.getVertices();
    for(size_t i = 0; i < image.height(); i++){
        for(size_t j = 0; j < image.width(); j++){
            auto ray = camera.castRay(static_cast<float>(j) / image.width(), 1 - static_cast<float>(i) /image.height());
            for(auto &triangle: scene.getTriangles()){
                auto&[i0, i1, i2] = triangle;
                std::optional<Vec3<float>> intersection = ray.intersect(points[i0], points[i1], points[i2]);
                if(intersection){
                    image(i,j) = {1.f, 0.f, 0.f};
                    std::cout << "kek" << std::endl;
                }
            }
        }
    }
}
