//
// Created by roundedglint585 on 1/29/21.
//

#ifndef RAYTRACER_WORLEYNOISE_H
#define RAYTRACER_WORLEYNOISE_H

#include <cstddef>
#include <vector>
#include <array>
#include "Random.h"

namespace randomGenerator {

    template<size_t Dim>
    class WorleyNoise {
    public:
        WorleyNoise(size_t featureCount);

        template<typename ...Args>
        float getValue(Args ...args) const;

        float getValue(const std::array<float, Dim> &point);

    private:
        float distance(const std::array<float, Dim> &first, const std::array<float, Dim> &second) const;

        std::vector<std::array<float, Dim>> features_m;
    };

    template<size_t Dim>
    WorleyNoise<Dim>::WorleyNoise(size_t featureCount) {
        features_m.reserve(featureCount);
        for (size_t i = 0; i < featureCount; i++) {
            std::array<float, Dim> toAdd;
            for (size_t j = 0; j < Dim; j++) {
                toAdd[j] = floatRandom(0.f, 1.f);
            }
            features_m.emplace_back(toAdd);
        }
    }


    template<size_t Dim>
    float WorleyNoise<Dim>::distance(const std::array<float, Dim> &first, const std::array<float, Dim> &second) const {
        float dist = 0.f;
        for (size_t i = 0; i < first.size(); i++) {
            dist += std::pow(first[i] - second[i], 2);
        }
        return std::sqrt(dist);
    }

    template<size_t Dim>
    template<typename ...Args>
    float WorleyNoise<Dim>::getValue(Args... args) const {
        std::array<float, Dim> point = {args...};
        return getValue(point);
    }

    template<size_t Dim>
    float WorleyNoise<Dim>::getValue(const std::array<float, Dim> &point) {
        float closestDistance = std::numeric_limits<float>::max();
        for (auto &feature: features_m) {
            if (distance(point, feature) < closestDistance) {
                closestDistance = distance(point, feature);
            }
        }
        return closestDistance;
    }
}


#endif //RAYTRACER_WORLEYNOISE_H
