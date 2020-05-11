#pragma once 
#include "../precompiled.h"

class Shader
{
private:
    /* data */

    const char *vertexSource ;
    const char *fragmentSource ;


    GLuint shader_program;

public:
    Shader(/* args */);
    ~Shader();

    void makeShader();
    void setShader();


};


