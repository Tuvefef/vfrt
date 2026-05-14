#ifndef _V_F_TIME_DEBUG_H
#define _V_F_TIME_DEBUG_H

#include <SDL2/SDL.h>

#include "camera/camera.h"
#include "scene/scene.h"

#include <stdio.h>
#include <time.h>

typedef void (*renderPixelsVoid)(camera*, scene*, int, int, int, int, SDL_Renderer*);

static inline void calcSceneLoadTime(renderPixelsVoid renderFn, camera* c, scene* s, int w, int h, int samples, int depth, SDL_Renderer* renderer)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    renderFn(c, s, w, h, samples, depth, renderer);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double telap = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    fprintf(stderr, "time load image: %.6f s\n", telap);
}

#endif