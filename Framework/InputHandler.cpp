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
    EMSCRIPTEN_KEEPALIVE void _keyboardDown(int key)
    {
        InputHandler::getInstance()->HandleEvent(key, true);
    }
    EMSCRIPTEN_KEEPALIVE void _keyboardUp(int key)
    {
        InputHandler::getInstance()->HandleEvent(key, false);
    }
#if __EMSCRIPTEN__
}
#endif

InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler()
{
    for (int i = 0; i < 128; i++)
    {
        KEYS[i] = false;
        // mykeyboardDown[i] = [i] {
        // //    std::cout << SDL_GetKeyName((SDL_Keycode)i) << " down , SDL KEYCODE : " << i << std::endl;
        // };
        // mykeyboardUp[i] = [i] {
        //  //   std::cout << SDL_GetKeyName((SDL_Keycode)i) << " up , SDL KEYCODE : " << i << std::endl;
        // };
    }

    std::cout << "Init InputHandler " << std::endl;
}

InputHandler::~InputHandler()
{
}

void InputHandler::HandleEvent(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
      //  std::cout << SDL_GetKeyName(event.key.keysym.sym) << " down , SDL KEYCODE : " << event.key.keysym.sym << std::endl;
        if (event.key.keysym.sym < 128)
        {
            _keyboardDown((int)event.key.keysym.sym);
            KEYS[event.key.keysym.sym] = true;
        }

        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym < 128)
        {
            _keyboardUp((int)event.key.keysym.sym);
            KEYS[event.key.keysym.sym] = false;
        }

        break;
    case SDL_MOUSEBUTTONDOWN:
        _clickLeft();
        break;
    default:
        break;
    }
}

void InputHandler::HandleEvent(int keycode, bool pressed)
{   
    if( pressed == true ){
        auto iter = mykeyboardDown.find(keycode);
        if( iter != mykeyboardDown.end()){
            (iter->second)();
        }
    }
    else {
        auto iter = mykeyboardUp.find(keycode);
        if( iter != mykeyboardUp.end()){
            (iter->second)();
        }
    }
}

void InputHandler::Delete()
{
    delete instance;
}

void InputHandler::Update(float deltaTime)
{
    //Pressed Event
}

bool InputHandler::SetKeyboardDownEvent(int id, std::function<void()> function ){
      mykeyboardDown.insert(std::pair<int, std::function<void()>>( id, function));
      return true;
}

bool InputHandler::SetKeyboardUpEvent(int id, std::function<void()> function ){
      mykeyboardUp.insert(std::pair<int, std::function<void()>>( id, function));
      return true;
}