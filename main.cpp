#include "./Framework/precompiled.h"

#define PI 3.14159265

Director *director;

static GLuint previous_ticks = 0;
static GLuint max_fps = 16;
static GLfloat lag = 0;

void loop()
{
    GLuint ticks = SDL_GetTicks();
    lag = ticks - previous_ticks;
    previous_ticks = ticks;

  //  while (lag > max_fps)
  // {
        director->Update(lag / 1000);
//        lag = 0;

  //  }
    director->Render();
}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int WinMain()
#else
int main()
#endif
{
    director = new Director();

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

    delete director;
    return 0;
}