#ifndef _V_F_RAYTRACER_SPHERE_H
#define _V_F_RAYTRACER_SPHERE_H

#include "../typ.h"
#include "../material/material.h"

typedef struct sphere 
{
    vec3 coord;
    float radius;
    material mat;
} sphere;

#endif