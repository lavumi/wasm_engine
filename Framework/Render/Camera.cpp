#include "../precompiled.h"
#include "Camera.h"

Camera::Camera(/* args */)
{
    fovy = 45.0f;
    aspect = 4.0f / 3.0f;
    near = 0.1f;
    far = 100.0f;

    position = glm::vec3(2, 3, -13);
    forward = glm::vec3(0, 0, 1);
    up = glm::vec3(0, 1, 0);

    setPerspective();
    setView();

    moveLeft = false;
    moveRight = false;
    moveFront = false;
    moveBack = false;
}

Camera::~Camera()
{
}

void Camera::setPerspective()
{
    projection = glm::perspective(glm::radians(fovy), aspect, near, far);
}

void Camera::setView()
{
    view = glm::lookAt(
        position,           // Camera is at (4,3,-3), in World Space
        forward + position, // and looks at the origin
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Camera::GetVP()
{
    return projection * view;
}

void Camera::SetTransform(glm::mat4 transform)
{
    view = transform * view;
}

void Camera::SetMoveBack(bool active)
{
    moveBack = active;
}
void Camera::SetMoveRight(bool active)
{
    moveRight = active;
}
void Camera::SetMoveFront(bool active)
{
    moveFront = active;
}
void Camera::SetMoveLeft(bool active)
{
    moveLeft = active;
}

void Camera::Update(float deltaTime)
{
    float speed = 3.0f;
    position.x -= moveRight * speed * deltaTime;
    position.x += moveLeft  * speed * deltaTime;
    position.z -= moveBack  * speed * deltaTime;
    position.z += moveFront * speed * deltaTime;
    setView();

  //  std::cout << position.x << std::endl;
}