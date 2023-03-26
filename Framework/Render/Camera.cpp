#include "../precompiled.h"
#include "Camera.h"

using namespace VumiEngine;

Camera::Camera(/* args */) {
    fovy = 45.0f;
    aspect = 4.0f / 3.0f;
    near = 0.1f;
    far = 100.0f;

    position = glm::vec3(0, 0, -13);
    forward = glm::vec3(0, 0, 1);
    up = glm::vec3(0, 1, 0);

    setPerspective();
    setView();

    moveLeft = false;
    moveRight = false;
    moveFront = false;
    moveBack = false;
}

Camera::~Camera() {
}

void Camera::setPerspective() {
    projection = glm::perspective(glm::radians(fovy), aspect, near, far);
}

void Camera::setView() {
    view = glm::lookAt(
            position,           // Camera is at (4,3,-3), in World Space
            forward + position, // and looks at the origin
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Camera::GetVP() {
    return projection * view;
}

void Camera::SetTransform(glm::mat4 transform) {
    view = transform * view;
}

void Camera::SetMoveBack(bool active) {
    moveBack = active;
}

void Camera::SetMoveRight(bool active) {
    moveRight = active;
}

void Camera::SetMoveFront(bool active) {
    moveFront = active;
}

void Camera::SetMoveLeft(bool active) {
    moveLeft = active;
}


// speed is usually 0.1f or something small like that
void Camera::SetRotate(float amount, glm::vec3 axis) {
    glm::mat4 iden(1.0f);
    iden = glm::rotate(iden, amount * 0.03f, axis);
    forward = iden * glm::vec4(forward, 0);
    //forward = glm::rotate(forward, amount * 3.0f, axis);
}

void Camera::SetTranslate(glm::vec3 &direction) {
    position -= direction;
}

void Camera::Update(float deltaTime) {
    float speed = 3.0f;
    glm::vec3 movement = glm::vec3(
            -moveLeft * speed * deltaTime + moveRight * speed * deltaTime,
            0,
            -moveFront * speed * deltaTime + moveBack * speed * deltaTime);
    SetTranslate(movement);
    setView();
}