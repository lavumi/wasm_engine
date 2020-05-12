#pragma once
class Camera
{
private:
    /* data */

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;

    GLfloat fovy;
    GLfloat aspect;
    GLfloat near;
    GLfloat far;


    glm::mat4 projection;
    glm::mat4 view;

    void setPerspective();
    void setView();



public:
    Camera(/* args */);
    ~Camera();

    glm::mat4 GetVP();
    void SetTransform( glm::mat4 transform );





    //움직임

    bool moveFront;
    bool moveBack;
    bool moveLeft;
    bool moveRight;


    void SetMoveLeft(bool active);
    void SetMoveRight(bool active);
    void SetMoveFront(bool active);
    void SetMoveBack(bool active);

    void Update();
};
