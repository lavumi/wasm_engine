#pragma once

#include "precompiled.h"

class TestCube
{
private:
    /* data */
public:
    TestCube(/* args */);
    ~TestCube();

    void makeBuffer();
    	GLuint vertexbuffer;
        	GLuint colorbuffer;

    void setBuffer();
};


