#pragma once

#include "precompiled.h"
class Shader;
class TestCube
{
private:
    /* data */

    glm::mat4 worldMatrix;

    GLuint shader;
public:
    TestCube(/* args */);
    ~TestCube();

    void makeBuffer();
    	GLuint vertexbuffer;
        	GLuint colorbuffer;

    void setBuffer(GLuint shaderProgram);

    void Update(float deltaTime);
    void Render();
};


