#pragma once

class Renderer;
class ThreeCube;
class Camera;
class Director
{
private:
    /* data */
public:
    Director(/* args */);
    ~Director();

    void Update(float deltaTime);
    void Render();

    Renderer* renderer;
    Camera* camera;
    ThreeCube *testCube;
};

