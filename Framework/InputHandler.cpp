#include "./precompiled.h"
#include "InputHandler.h"


#if __EMSCRIPTEN__
extern "C" {
#else
#define EMSCRIPTEN_KEEPALIVE 
#endif
    EMSCRIPTEN_KEEPALIVE void _clickLeft(){     InputHandler::getInstance()->myfxClickLeft(); }
#if __EMSCRIPTEN__
}
#endif








InputHandler* InputHandler::instance = nullptr;

InputHandler::InputHandler(){
}

InputHandler::~InputHandler()
{

}

void InputHandler::HandleEvent(SDL_Event event){
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        _clickLeft();
    }
}

void InputHandler::Delete(){
    delete instance;
}



