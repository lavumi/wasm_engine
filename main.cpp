#include "./Framework/precompiled.h"

#define PI 3.14159265




#if __EMSCRIPTEN__
extern "C" {
#else
#define EMSCRIPTEN_KEEPALIVE 
#endif
    EMSCRIPTEN_KEEPALIVE void _clickLeft(){ InputHandler::myfxClickLeft(); }
#if __EMSCRIPTEN__
}
#endif



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
        updateTriangle();
    }
    renderer->Render();

}


int main()
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

            if(e.type == SDL_MOUSEBUTTONDOWN) _clickLeft();
        }
        loop();
    }
#endif

    delete renderer;
    return 0;
}