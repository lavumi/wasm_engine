#pragma once 
#include "../precompiled.h"

class Shader
{
private:
    /* data */

    const char *vertexSource ;
    const char *fragmentSource ;




public:
    GLuint shader_program;
    Shader(/* args */);
    ~Shader();

    void makeShader();
    void setShader();

    void Update();

    glm::mat4 Model;
};


