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
    Image(size_t width, size_t height) : width_m(width), height_m(height), image_m(width * height, {0.0f, 0.0f, 0.0f}) {

    }

    Image(size_t width, size_t height, float color) : width_m(width), height_m(height), image_m(width * height,
                                                                                                {color, color, color}) {

    }

    Image(size_t width, size_t height, std::array<float, 3> color) : width_m(width), height_m(height),
                                                                     image_m(width * height, Vec3(color)) {

    }

    void writeImage(const std::string &path) const {
        std::ofstream file(path);
        if (file) {
            file << "P3\n";
            file << width_m << " " << height_m << "\n";
            file << 255.0 << "\n";
            for (auto &i: image_m) {
                for (size_t j = 0; j < 3; j++) {
                    file << static_cast<int>(std::clamp(i[j], 0.f, 1.f) * 255.0) << " ";
                }
                file << "\n";
            }
        } else {
            std::cerr << "file opening error" << std::endl;
        }
    }

    void fillBackgroundWithGradient(std::array<float, 3> from, std::array<float, 3> to) {
        std::array<float, 3> step = {(to[0] - from[0]) / height_m, (to[1] - from[1]) / height_m,
                                     (to[2] - from[2]) / height_m};
#pragma omp parallel default(none) shared(from, to, step)
        for (size_t i = 0; i < height_m; i++) {
            Vec3 newColor = {from[0] + step[0] * i, from[1] + step[1] * i, from[2] + step[2] * i};
#pragma omp parallel default(none) shared(newColor, i)
            for (size_t j = 0; j < width_m; j++) {
                image_m[i * width_m + j] = newColor;
            }
        }
    }

    size_t width() const { return width_m; }

    size_t height() const { return height_m; }

    const Vec3<float> &operator()(size_t x, size_t y) const { return image_m[y * width_m + x]; }

    Vec3<float> &operator()(size_t x, size_t y) { return image_m[y * width_m + x]; }

private:
    size_t width_m, height_m;
    std::vector<Vec3<float>> image_m;
};


#endif //RAYTRACER_IMAGE_H
