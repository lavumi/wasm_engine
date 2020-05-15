#pragma once 
#include "../precompiled.h"


class Camera;
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

    void SetUniformMatrix4fv(std::string name, GLfloat* value );
    glm::mat4 Model;
};


