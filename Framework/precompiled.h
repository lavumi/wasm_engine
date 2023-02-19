#pragma once
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif


#include <cstdlib>
#include <map>
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>





#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>


#include "../libs/glm/glm.hpp"
#include "../libs/glm/common.hpp"
#include "../libs/glm/gtc/quaternion.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"




#include "Node.h"
#include "Director.h"
#include "InputHandler.h"
#include "Render/Renderer.h"


#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1200
