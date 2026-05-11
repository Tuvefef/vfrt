#ifndef _V_F_RAYTRACER_CAMERA_H
#define _V_F_RAYTRACER_CAMERA_H

#include "../vec3/vec3.h"
#include "../scene/scene.h"

typedef struct
{
    int imageWidth;
    int imageHeight;

    float aspectRatio;
    float viewportWidth;
    float viewportHeight;
    float focalLength;
    float vfov;

    vec3 lookFromCam;
    vec3 lookAtCam;
    vec3 vup;

    vec3 u;
    vec3 v;
    vec3 w;

    vec3 coord;
    vec3 horizontal;
    vec3 vertical;
    vec3 lowerLeftCorner;
} camera;

ray setCameraGetRay(camera* c, float u, float v);
void initCameraRender(camera* c, int imageWidth, int imageHeight, float vfov, vec3 lookFromCam, vec3 lookAtCam, vec3 vup);

#endif
