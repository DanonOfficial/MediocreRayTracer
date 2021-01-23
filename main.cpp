#include <iostream>
#include "Image.h"
#include "Scene.h"

int main(int argc, char *argv[]) {
    size_t width, height;
    std::string path;
    for(int i = 0; i < argc; i++){
        if(std::string(argv[i]) == "-width"){
            width = std::stoll(argv[i+1]);
        }else if(std::string(argv[i]) == "-height"){
            height = std::stoll(argv[i+1]);
        }else if(std::string(argv[i]) == "-output"){
            path = argv[i+1];
        }
    }
    Image image(width, height);
    image.fillBackgroundWithGradient({1, 1, 1}, {0, 0, 1.f});
    image.writeImage(path);
    std::vector<Vec3<float>> vertices = {{0.0f, 0.0f, -1.f}, {1.f, 0.f, -1.f}, {0.f, 1.f, -1.f}};
    std::vector<Vec3<size_t>> triangles = {{0,1,2}};
    Scene scene(vertices, triangles);
    return 0;
}
