//
// Created by roundedglint585 on 1/27/21.
//

#ifndef RAYTRACER_RANDOM_H
#define RAYTRACER_RANDOM_H
#include <random>
namespace randomGenerator{
    static thread_local std::mt19937 generator;
    inline float floatRandom(const float min, const float max) {
        std::uniform_real_distribution<float> distribution(min,max);
        return distribution(generator);
    }
}
#endif //RAYTRACER_RANDOM_H
