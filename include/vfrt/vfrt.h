#ifndef _V_F_RAYTRACER
#define _V_F_RAYTRACER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vec3/vec3.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "material/material.h"

#ifdef VF_CALC_EXEC_TIME_SCN
#include "vftm.h"
#endif

void initRenderImg(int imageWidth, int imageHeight);
void renderSceneImg(camera* c, scene* s, int imageWidth, int imageHeight, int samples, int maxDepth);

#endif