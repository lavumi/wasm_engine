#pragma once
#include "../precompiled.h"

class TestCube;
class Shader;
class Renderer
{
private:
    void makeShader();

    SDL_Window *window = NULL;
    SDL_GLContext context;


    Shader* shader;

    TestCube* testCube;

public:
    Renderer(/* args */);
    ~Renderer();

    void Init();
    void Update();
    void Render();

    GLfloat rotation_angle;
    GLuint length_of_attributes;
    GLuint vbo;

    const char *vertexSource;

    const char *fragmentSource;

    bool background_is_black = true;
};
