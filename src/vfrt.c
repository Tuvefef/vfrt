#include "../include/vfrt/vfrt.h"

#define printRgbValues(r, g, b) printf("%d %d %d\n", (r), (g), (b))

#define ___VF_RAND
#ifdef  ___VF_RAND

static uint64_t hstate = 0x123456789abcdef0ULL;

static uint32_t uxorShift32(void)
{
    hstate = hstate ^ hstate << 13;
    hstate = hstate ^ hstate >> 7;
    hstate = hstate ^ hstate << 17;

    return (uint32_t)((hstate * 0x2545f4914f6cdd1dULL) >> 32);
}

float uxorShift32f(void)
{
    return (float)uxorShift32() * (1.0f / (float)0x100000000);
}

#endif // ___VF_RAND

void initWindow()
{
    SDL_Init(SDL_INIT_VIDEO);
}

static void outFinalColor(vec3 color, SDL_Renderer* renderer, int i, int j) 
{
    uint8_t r = (uint8_t)(255.999 * linearToSrgb(color.x));
    uint8_t g = (uint8_t)(255.999 * linearToSrgb(color.y));
    uint8_t b = (uint8_t)(255.999 * linearToSrgb(color.z));

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, i, j);
}

VFRayTWindow* createWindow(const char* windowName, int imageWidth, int imageHeight)
{
    return SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, imageWidth, imageHeight, SDL_WINDOW_SHOWN);
}

VFRayTRenderer* createRenderer(VFRayTWindow* window)
{
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void renderScenePixels(camera* c, scene* s, int imageWidth, int imageHeight, int samples, int maxDepth, VFRayTRenderer* renderer)
{
    for (int j = 0; j < imageHeight; j++)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            vec3 color = setvec3(0.0f, 0.0f, 0.0f);
            for (int sp = 0; sp < samples; sp++)
            {
                float u = ((float)i + uxorShift32f()) / (imageWidth - 1);
                float v = ((float)j + uxorShift32f()) / (imageHeight - 1);

                ray r = setCameraGetRay(c, u, v);
                color = addvec3(color, rayColor(&r, s, maxDepth));
            }

            color = sclmvec3(color, 1.0f / samples);
            outFinalColor(color, renderer, i, j);
        }
    }

    SDL_RenderPresent(renderer);
}

void windowPollEvent(void)
{
    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
                running = false;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
                running = false;
        }
    }
}

void destroyWindow(VFRayTWindow* window)
{
    SDL_DestroyWindow(window);
}

void destroyRenderer(VFRayTRenderer* renderer)
{
    SDL_DestroyRenderer(renderer);
}

void finishWindow(void)
{
    SDL_Quit();
}