//
// Created by roundedglint585 on 1/9/21.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include "thirdParty/Vec3.h"

class Image {
public:
    Image(size_t width, size_t height) : width(width), height(height), image_(width * height, {0.0f, 0.0f, 0.0f}) {

    }

    Image(size_t width, size_t height, float color) : width(width), height(height), image_(width * height,
                                                                                           {color, color, color}) {

    }

    Image(size_t width, size_t height, std::array<float, 3> color) : width(width), height(height),
                                                                     image_(width * height, color) {

    }

    void writeImage(const std::string &path) const {
        std::ofstream file(path);
        if(file){
            file << "P3\n";
            file << width << " " << height << "\n";
            file << 255.0 << "\n";
            for (auto &i: image_) {
                for(size_t j = 0; j < 3; j++){
                    file << static_cast<int>(std::clamp(i[j], 0.f, 1.f) * 255.0) << " ";
                }
//                for(auto j: i){
//                    file << static_cast<int>(std::clamp(j, 0.f, 1.f) * 255.0) << " ";
//                }
                file << "\n";
            }
        }else{
            std::cerr <<"file opening error" << std::endl;
        }
    }

    void fillBackgroundWithGradient(std::array<float, 3> from, std::array<float, 3> to) {
        std::array<float, 3> step = {(to[0] - from[0]) / height, (to[1] - from[1]) / height,
                                     (to[2] - from[2]) / height};
        #pragma omp parallel default(none) shared(from, to, step)
        for (size_t i = 0; i < height; i++) {
            std::array<float, 3> newColor = {from[0] + step[0] * i, from[1] + step[1] * i, from[2] + step[2] * i};
            #pragma omp parallel default(none) shared(newColor, i)
            for (size_t j = 0; j < width; j++) {
                image_[i * width + j] = newColor;
            }
        }
    }

private:
    size_t width, height;
    std::vector<Vec3<float>> image_;
};


#endif //RAYTRACER_IMAGE_H
