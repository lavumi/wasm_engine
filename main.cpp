#include "./Framework/precompiled.h"

#define PI 3.14159265

Renderer* renderer;

static GLuint previous_ticks = 0;
static GLuint max_fps = 16;
static GLfloat lag = 0;



void loop(){
    GLuint ticks = SDL_GetTicks();
    lag += ticks - previous_ticks;
    previous_ticks = ticks;

    while (lag > max_fps)
    {
        lag -= max_fps;
        renderer->Update();
    }
    renderer->Render();

}


void WinMain()
{
    renderer = new Renderer();
    renderer->Init();


#if __EMSCRIPTEN__
    emscripten_set_main_loop(loop, -1, 1);
#else
    SDL_Event e;
    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                break;
            InputHandler::getInstance()->HandleEvent(e);
        }
        loop();
    }
#endif

    delete renderer;
    return;
}



// g++ main.cpp Framework/InputHandler.cpp Framework/Render/Render.cpp Framework/Render/Shader.cpp Framework/TestCube.cpp -std=c++17 -Wall -lopengl32 -lSDL2 -lglew32 -g -o build/win/app.exe