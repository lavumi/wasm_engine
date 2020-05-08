#pragma once
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <cmath>
#include <string>
#include <math.h>

#include "InputHandler.h"
#include "Renderer.h"



