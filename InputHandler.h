namespace Input{
    std::function<void()> clickLeft;
}

#if __EMSCRIPTEN__
extern "C" {
#else
#define EMSCRIPTEN_KEEPALIVE 
#endif
   EMSCRIPTEN_KEEPALIVE void _clickLeft(){Input::clickLeft();}
#if __EMSCRIPTEN__
}
#endif