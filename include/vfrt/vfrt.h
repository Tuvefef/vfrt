#ifndef _V_F_RAYTRACER
#define _V_F_RAYTRACER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vec3/vec3.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "material/material.h"

#define printRgbValues(r, g, b) printf("%d %d %d\n", (r), (g), (b))

void initRenderImg(int imgw, int imgh);
void renderSceneImg(camera* c, scene* s, int imageWidth, int imageHeight, int samples, int maxDepth);

#endif
