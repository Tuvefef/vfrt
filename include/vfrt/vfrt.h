#ifndef _V_F_RAYTRACER
#define _V_F_RAYTRACER

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>

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

typedef SDL_Window VFRayTWindow;
typedef SDL_Renderer VFRayTRenderer;

void initWindow(void);

VFRayTWindow* createWindow(const char* windowName, int imageWidth, int imageHeight);
VFRayTRenderer* createRenderer(VFRayTWindow* window);

void windowPollEvent(void);

void destroyWindow(VFRayTWindow* window);
void destroyRenderer(VFRayTRenderer* renderer);
void finishWindow(void);

void renderScenePixels(camera* c, scene* s, int imageWidth, int imageHeight, int samples, int maxDepth, VFRayTRenderer* renderer);

#endif
