#ifndef _V_F_RAYTRACER_SCENE_H
#define _V_F_RAYTRACER_SCENE_H

#include <math.h>
#include "../typ.h"
#include "../material/material.h"

#define MSPHERES 512
#define inverseValue(x) (1.0f - (x))
#define PI 3.1415

static float degreesToRadians(float degrees)
{
    return degrees * PI / 180.0f;
}

typedef struct 
{
    vec3 coord;
    float radius;
    material mat;
} sphere;

typedef struct 
{
    sphere s[MSPHERES];
    int count;
} scene;

ray makeSetRay(vec3 origin, vec3 direction);
sphere setSphere(vec3 coord, float radius, material mat);
vec3 rayColor(ray* r, scene* s, int depth);
void addElementInScene(scene* sn, sphere sp);

#endif
