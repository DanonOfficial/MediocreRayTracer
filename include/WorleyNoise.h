//
// Created by roundedglint585 on 1/29/21.
//

#ifndef RAYTRACER_WORLEYNOISE_H
#define RAYTRACER_WORLEYNOISE_H
#include <cstddef>
#include <vector>
#include <array>
#include "Random.h"
namespace random {

    template<size_t Dim>
    class WorleyNoise {
    public:
        WorleyNoise(size_t featureCount);

        template <typename ...Args>
        float getValue(Args ...args) const;

    private:
        float distance(const std::array<float, Dim> &first, const std::array<float, Dim> &second) const;
        std::vector<std::array<float, Dim>> features_m;
    };

    template<size_t Dim>
    WorleyNoise<Dim>::WorleyNoise(size_t featureCount) {
        features_m.reserve(featureCount);
        for(size_t i = 0; i < featureCount; i++){
            features_m.emplace_back(floatRandom(0.f, 1.f), floatRandom(0.f, 1.f),  floatRandom(0.f, 1.f),  floatRandom(0.f, 1.f));
        }
    }

    template<size_t Dim, typename... Args>
    float WorleyNoise<Dim>::getValue(Args... args) const {
        array<float, Dim> point = {args...};
        size_t closestIndex = -1;
        float closestDistance = std::numeric_limits<float>::max();
        for(size_t i = 0; i < features_m.size(); i++){
            if(distance(point, features_m[i]) < closestDistance){
                closestDistance = distance(point, features_m[i]);
                closestIndex = i;
            }
        }
        return closestDistance;
    }

    template<size_t Dim>
    float WorleyNoise<Dim>::distance(const std::array<float, Dim> &first, const std::array<float, Dim> &second) const {
        float dist = 0.f;
        for(size_t i = 0; i < first.size(); i++){
            dist += std::pow(first[i] - second[i], 2);
        }
        return std::sqrt(dist);
    }

}


#endif //RAYTRACER_WORLEYNOISE_H
