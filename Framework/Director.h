#pragma once

class Renderer;
class Camera;
class Director
{
private:
    /* data */
public:
    Director(/* args */);
    ~Director();

    void Update();
    void Render();

    Renderer* renderer;
    Camera* camera;
};

