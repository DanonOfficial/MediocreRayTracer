#include <iostream>
#include "image.h"
int main(int argc, char *argv[]) {
    size_t width, height;
    std::string path;
    for(size_t i = 0; i < argc; i++){
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

    return 0;
}
