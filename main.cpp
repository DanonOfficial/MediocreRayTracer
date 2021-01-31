#include <iostream>
#include "include/Image.h"
#include "include/Scene.h"
#include "include/RayCaster.h"
#include "include/Mesh.h"
#include "include/AreaLightSource.h"
#include "include/BVH.h"

int main(int argc, char *argv[]) {
    size_t width, height;
    std::string path;
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-width") {
            width = std::stoll(argv[i + 1]);
        } else if (std::string(argv[i]) == "-height") {
            height = std::stoll(argv[i + 1]);
        } else if (std::string(argv[i]) == "-output") {
            path = argv[i + 1];
        }
    }
    Image image(width, height);
    //image.fillBackgroundWithGradient({1, 1, 1}, {0, 0, 1.f});
    Scene scene;
    Mesh meshForScene;
    Material baseMaterial = {{1.f, 1.f, 1.f}, .2f, 1.f, {0.1f, 0.1f, 0.1f}};
    //const Vec3<float> &albedo, float diffuseCoeff, float roughness_m, Vec3<float> &refractionIndex
    meshForScene.loadOFF("resources/ball.off");
    meshForScene.setMaterial(baseMaterial);
    Mesh ground;
    ground.loadOFF("resources/ground.off");
    ground.setMaterial(baseMaterial);
    scene.addMesh(meshForScene);
    scene.addMesh(ground);
    //(const Vec3<float> &position, const Vec3<float> &direction, const Vec3<float> &color, float intensity, float squareSize);
    AreaLightSource lightSource = AreaLightSource({2.f, 2.f, 2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, 1.f, 0.2f);
    scene.addLightSource(lightSource);
////    randomGenerator::WorleyNoise<2> worley(50);
////    for(size_t i = 0; i < width; i++){
////        for(size_t j = 0; j < height; j++){
////            float value = worley.getValue(float(i)/width, float(j)/height);
////            image(j, i) = {value, value, value};
////        }
////    }
//
    scene.buildBVH();
    RayCaster renderer;
    renderer.render(scene, image, 16);
    image.writeImage(path);
    return 0;
}
