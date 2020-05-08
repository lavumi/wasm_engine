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

#include "InputHandler.h"
#include "Renderer.h"

static float attributes[] = {
    0.0f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,

    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,

    -0.5f,
    -0.5f,
    0.0f,
    0.0f,
    1.0f,
};
static GLfloat rotation_angle = -0.01;
static GLuint length_of_attributes = sizeof(attributes) / sizeof(attributes[0]);
static GLuint vbo;

static const char *vertexSource = R"glsl(
#version 100
attribute vec2 position;
attribute vec3 color;
varying vec3 vColor;
void main()
{
  vColor = color;
  gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

static const char *fragmentSource = R"glsl(
#version 100
precision mediump float;
varying vec3 vColor;
void main()
{
    gl_FragColor = vec4(vColor, 1.0);
}
)glsl";

static bool background_is_black = true;




//todo 바꿀곳
static void updateTriangle(){
    for (GLuint i = 0; i < length_of_attributes; i = i + 5)
    {
        float x = attributes[i];
        float y = attributes[i + 1];

        attributes[i] = x * std::cosf(rotation_angle) - y * std::sinf(rotation_angle);
        attributes[i + 1] = y * std::cosf(rotation_angle) + x * std::sinf(rotation_angle);
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);
}