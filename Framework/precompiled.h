#pragma once
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif


#include <functional>
#include <iostream>
#include <cmath>
#include <string>
#include <math.h>



#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>


#include "InputHandler.h"
#include "Render/Renderer.h"



