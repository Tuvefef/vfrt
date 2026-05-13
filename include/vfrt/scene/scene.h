#ifndef _V_F_RAYTRACER_SCENE_H
#define _V_F_RAYTRACER_SCENE_H

#include "../vfmt.h"
#include "../typ.h"
#include "../material/material.h"
#include "../scene/sphere.h"

#ifdef VF_INC_BVH
#include "../bvh/bvh.h"
#endif

typedef struct
{
    sphere s[MSPHERES];
    int count;

#ifdef VF_INC_BVH
    bvh tree;
    int bvhb;
#endif
} scene;

ray makeSetRay(vec3 origin, vec3 direction);
sphere setSphere(vec3 coord, float radius, material mat);
vec3 rayColor(ray* r, scene* s, float depth);

void renderSceneWithBvh(scene* s);
void addElementInScene(scene* sn, sphere sp);

#endif