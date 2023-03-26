#include "./precompiled.h"
#include "InputHandler.h"

using namespace VumiEngine;
#if __EMSCRIPTEN__
extern "C"
{
#else
#define EMSCRIPTEN_KEEPALIVE
#endif
    EMSCRIPTEN_KEEPALIVE void _mouseLeftDown()
    {
        InputHandler::getInstance()->myfxMouseLeftDown();
    }
    EMSCRIPTEN_KEEPALIVE void _mouseLeftUp()
    {
        InputHandler::getInstance()->myfxMouseLeftUp();
    }
    EMSCRIPTEN_KEEPALIVE void _keyboardDown(int key)
    {
        InputHandler::getInstance()->HandleEvent(key, true);
    }
    EMSCRIPTEN_KEEPALIVE void _keyboardUp(int key)
    {
        InputHandler::getInstance()->HandleEvent(key, false);
    }
    EMSCRIPTEN_KEEPALIVE void _mouseMove(int deltaX, int deltaY)
    {
        InputHandler::getInstance()->HandleMouseInput(deltaX, deltaY);
    }
#if __EMSCRIPTEN__
}
#endif

InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler()
{
    setKeyCode();
}

InputHandler::~InputHandler()
{
    mouseMoveEvent = [](int inputX, int inputY){
        std::cout << inputX << "     " << inputY << std::endl;
    };
}

void InputHandler::setKeyCode()
{
    keycode[8] = SDLK_BACKSPACE; //backspace
    keycode[9] = SDLK_TAB;       //tab
    keycode[13] = SDLK_RETURN;   //enter
    keycode[16] = SDLK_LSHIFT;   //shift
    keycode[17] = SDLK_LCTRL;    //ctrl
    keycode[18] = SDLK_LALT;     //alt
    keycode[19] = SDLK_PAUSE;    //pause/break
    keycode[20] = SDLK_CAPSLOCK; //caps lock
    keycode[27] = SDLK_ESCAPE;   //escape
    keycode[33] = SDLK_PAGEUP;   //page up
    keycode[34] = SDLK_PAGEDOWN; //page down
    keycode[35] = SDLK_END;      //end
    keycode[36] = SDLK_HOME;     //home
    keycode[37] = SDLK_LEFT;     //left arrow
    keycode[38] = SDLK_UP;       //up arrow
    keycode[39] = SDLK_RIGHT;    //right arrow
    keycode[40] = SDLK_DOWN;     //down arrow
    keycode[45] = SDLK_INSERT;   //insert
    keycode[46] = SDLK_DELETE;   //delete
    keycode[48] = SDLK_0;        //0
    keycode[49] = SDLK_1;        //1
    keycode[50] = SDLK_2;        //2
    keycode[51] = SDLK_3;        //3
    keycode[52] = SDLK_4;        //4
    keycode[53] = SDLK_5;        //5
    keycode[54] = SDLK_6;        //6
    keycode[55] = SDLK_7;        //7
    keycode[56] = SDLK_8;        //8
    keycode[57] = SDLK_9;        //9
    keycode[65] = SDLK_a;        //a
    keycode[66] = SDLK_b;        //b
    keycode[67] = SDLK_c;        //c
    keycode[68] = SDLK_d;        //d
    keycode[69] = SDLK_e;        //e
    keycode[70] = SDLK_f;        //f
    keycode[71] = SDLK_g;        //g
    keycode[72] = SDLK_h;        //h
    keycode[73] = SDLK_i;        //i
    keycode[74] = SDLK_j;        //j
    keycode[75] = SDLK_k;        //k
    keycode[76] = SDLK_l;        //l
    keycode[77] = SDLK_m;        //m
    keycode[78] = SDLK_n;        //n
    keycode[79] = SDLK_o;        //o
    keycode[80] = SDLK_p;        //p
    keycode[81] = SDLK_q;        //q
    keycode[82] = SDLK_r;        //r
    keycode[83] = SDLK_s;        //s
    keycode[84] = SDLK_t;        //t
    keycode[85] = SDLK_u;        //u
    keycode[86] = SDLK_v;        //v
    keycode[87] = SDLK_w;        //w
    keycode[88] = SDLK_x;        //x
    keycode[89] = SDLK_y;        //y
    keycode[90] = SDLK_z;        //z
    //keycode[91]  = SDLK_WIN;                                //left window key
    //keycode[92]  = SDLK_;                                //right window key
    keycode[93] = SDLK_SELECT;       //select key
    keycode[96] = SDLK_KP_0;         //numpad 0
    keycode[97] = SDLK_KP_1;         //numpad 1
    keycode[98] = SDLK_KP_2;         //numpad 2
    keycode[99] = SDLK_KP_3;         //numpad 3
    keycode[100] = SDLK_KP_4;        //numpad 4
    keycode[101] = SDLK_KP_5;        //numpad 5
    keycode[102] = SDLK_KP_6;        //numpad 6
    keycode[103] = SDLK_KP_7;        //numpad 7
    keycode[104] = SDLK_KP_8;        //numpad 8
    keycode[105] = SDLK_KP_9;        //numpad 9
    keycode[106] = SDLK_KP_MULTIPLY; //multiply
    keycode[107] = SDLK_KP_PLUS;     //add
    keycode[109] = SDLK_KP_MINUS;    //subtract
    keycode[110] = SDLK_KP_DECIMAL;  //decimal point
    keycode[111] = SDLK_KP_DIVIDE;   //divide
    keycode[112] = SDLK_F1;          //f1
    keycode[113] = SDLK_F2;          //f2
    keycode[114] = SDLK_F3;          //f3
    keycode[115] = SDLK_F4;          //f4
    keycode[116] = SDLK_F5;          //f5
    keycode[117] = SDLK_F6;          //f6
    keycode[118] = SDLK_F7;          //f7
    keycode[119] = SDLK_F8;          //f8
    keycode[120] = SDLK_F9;          //f9
    keycode[121] = SDLK_F10;         //f10
    keycode[122] = SDLK_F11;         //f11
    keycode[123] = SDLK_F12;         //f12
}

void InputHandler::HandleEvent(SDL_Event event)
{

    switch (event.type)
    {
    case SDL_KEYDOWN:
        _keyboardDown(event.key.keysym.sym);
        break;
    case SDL_KEYUP:
        _keyboardUp(event.key.keysym.sym);
        break;
    case SDL_MOUSEBUTTONDOWN:
        _mouseLeftDown();
        break;

    case SDL_MOUSEBUTTONUP:
        _mouseLeftUp();
        break;

    case SDL_MOUSEMOTION:
      //  std::cout << event.motion.x << "     " << event.motion.y << std::endl;
        HandleMouseInput(event.motion);
        break;
    default:
        break;
    }
}

void InputHandler::HandleEvent(int pKeyCode, bool pressed)
{
    int input = sanitizeInput(pKeyCode);
    if (pressed == true)
    {
        auto iter = mykeyboardDown.find(input);
        if (iter != mykeyboardDown.end())
        {
            (iter->second)();
        }
        else{
            std::cout << "not bind :  " << input << std::endl;
        }
    }
    else
    {
        auto iter = mykeyboardUp.find(input);
        if (iter != mykeyboardUp.end())
        {
            (iter->second)();
        }
        else{
            std::cout << "not bind :  " << input << std::endl;
        }
    }
}

void InputHandler::HandleMouseInput( SDL_MouseMotionEvent mouseMotion ) const{
    mouseMoveEvent( mouseMotion.xrel, mouseMotion.yrel);
}

void InputHandler::HandleMouseInput( int deltaX, int deltaY ) const{

    mouseMoveEvent( deltaX, deltaY);
}

void InputHandler::Delete()
{
    delete instance;
}

void InputHandler::Update(float deltaTime)
{
    //Pressed Event
}

bool InputHandler::SetKeyboardDownEvent(int id, const std::function<void()>& function)
{
    mykeyboardDown.insert(std::pair<int, std::function<void()>>(id, function));
    return true;
}

bool InputHandler::SetKeyboardUpEvent(int id, const std::function<void()> function)
{
    mykeyboardUp.insert(std::pair<int, std::function<void()>>(id, function));
    return true;
}

int InputHandler::sanitizeInput(int input)
{
#if __EMSCRIPTEN__
    return keycode[input];
#else
    return input;
#endif
}