#include "./precompiled.h"
#include "InputHandler.h"

#if __EMSCRIPTEN__
extern "C"
{
#else
#define EMSCRIPTEN_KEEPALIVE
#endif
    EMSCRIPTEN_KEEPALIVE void _clickLeft()
    {
        InputHandler::getInstance()->myfxClickLeft();
    }
    EMSCRIPTEN_KEEPALIVE void _keyboardDown(int key) { 
        InputHandler::getInstance()->mykeyboardInput[key]();
    }
    EMSCRIPTEN_KEEPALIVE void _keyboardUp(int key) {  
            std::cout << SDL_GetKeyName((SDL_Keycode)key) << " up , SDL KEYCODE : " <<  std::endl; 
     }
#if __EMSCRIPTEN__
}
#endif

InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler()
{
    for (int i = 0; i < 322; i++)
    {
        KEYS[i] = false;
        mykeyboardInput[i] = [i]{
            std::cout << SDL_GetKeyName((SDL_Keycode)i) << " down , SDL KEYCODE : " << i<<  std::endl; 
        };
    }

}

InputHandler::~InputHandler()
{
}

void InputHandler::HandleEvent(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        //_keyboardDown(SDL_GetKeyName(event.key.keysym.sym));
        _keyboardDown((int)event.key.keysym.sym);
        KEYS[event.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        //_keyboardUp(SDL_GetKeyName(event.key.keysym.sym));
        _keyboardUp((int)event.key.keysym.sym);
        KEYS[event.key.keysym.sym] = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        _clickLeft();
        break;
    default:
        break;
    }
}

void InputHandler::Delete()
{
    delete instance;
}

void InputHandler::Update(){
    //Pressed Event
}