//
// Created by roundedglint585 on 1/23/21.
//

#ifndef RAYTRACER_RAYCASTER_H
#define RAYTRACER_RAYCASTER_H


#include "Image.h"
#include "Scene.h"

class RayCaster {
public:
    void render(const Scene &scene, Image &image) const;
private:

};


#endif //RAYTRACER_RAYCASTER_H
