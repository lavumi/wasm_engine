#include "./Framework/precompiled.h"
#include "./src/TestScene.h"
#define PI 3.14159265

using namespace VumiEngine;

//Director *director;
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
    Director::GetDirector().Update(lag / 1000);
//        lag = 0;

  //  }
    Director::GetDirector().Render();
}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int WinMain()
#else
int main()
#endif
{
    Director::GetDirector();



    TestScene * testScene = new TestScene();
    testScene->Init();
    Director::GetDirector().AddScene(testScene);
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
            InputHandler::GetInputHandler().HandleEvent(e);
        }
        loop();
    }
#endif
    return 0;
}