#include <iostream>
#include "camera.hpp"
#include "entity.hpp"

Camera::Camera(float xPos, float yPos) {
    this -> x = xPos;
    this -> y = yPos;
    this -> frame = 0;
}

float Camera::getx() {
    return this -> x;
}

float Camera::gety() {
    return this -> y;
}

Uint32 Camera::getframe() {
    return this -> frame;
}

void Camera::setx(float xPos) {
    this -> x = xPos;
}

void Camera::sety(float yPos) {
    this -> y = yPos;
}

void Camera::setframe(Uint32 amount) {
    this -> frame = amount;
}

void Camera::displayPos() {
    std::cout << "Camera position: [" << this -> x << ", " << this -> y << "]" << std::endl;
}

float Camera::centerX(Entity &entity) {
    this -> x = entity.getx() - 200;
    return this -> x;
}