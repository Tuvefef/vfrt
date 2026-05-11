#ifndef _V_F_RAYTRACER_TYPES_H
#define _V_F_RAYTRACER_TYPES_H

#include <stdbool.h>
#include "vec3/vec3.h"

typedef struct 
{
    vec3 origin;
    vec3 direction;
} ray;

typedef struct material material;

typedef struct 
{
    vec3     p;
    vec3     n;
    float    t;
    bool     f;
    material* mat;
} hrecord;

#endif