#pragma once
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <map>
#include <functional>
#include <iostream>
#include <cmath>
#include <string>
#include <math.h>



#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Director.h"
#include "InputHandler.h"
#include "Render/Renderer.h"


#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1200
