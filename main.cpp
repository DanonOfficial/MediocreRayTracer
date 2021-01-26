#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "RayCaster.h"
#include "Mesh.h"

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
    Material baseMaterial = {{1.f, 1.f, 1.f}, .5f};
    meshForScene.loadOFF("resources/example.off");
    meshForScene.setMaterial(baseMaterial);
    Mesh ground;
    ground.loadOFF("resources/ground.off");
    ground.setMaterial(baseMaterial);
    scene.addMesh(meshForScene);
    scene.addMesh(ground);
    LightSource lightSource = {{2.f, 2.f, 2.f}, {1.f, 1.f, 1.f}, 1.f};
    scene.addLightSource(lightSource);
    RayCaster renderer;
    renderer.render(scene, image);
    image.writeImage(path);
    return 0;
}
