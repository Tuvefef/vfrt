#ifndef _V_F_TIME_DEBUG_H
#define _V_F_TIME_DEBUG_H

#include "camera/camera.h"
#include "scene/scene.h"

#include <stdio.h>
#include <time.h>

typedef void (*sceneImgVoid)(camera*, scene*, int, int, int, int);

static inline void calcSceneExecTime(sceneImgVoid snimg, camera* c, scene* s, int w, int h, int samples, int depth)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    snimg(c, s, w, h, samples, depth);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double telap = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    fprintf(stderr, "time render: %.6f s\n", telap);
}

#endif