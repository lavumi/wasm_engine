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

    void Update(float deltaTime);
    void Render();

    Renderer* renderer;
    Camera* camera;
};

