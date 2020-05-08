#pragma once
#include "precompiled.h"
class Renderer
{
private:
    /* data */

    void makeShader();

    SDL_Window *window = NULL;
    SDL_GLContext context;
public:
    Renderer(/* args */);
    ~Renderer();


    void Init();
    void Render();
};
