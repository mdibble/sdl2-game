#include <iostream>
#include "camera.hpp"
#include "entity.hpp"

Camera::Camera(float xPos, float yPos) {
    this -> x = xPos;
    this -> y = yPos;
}

float Camera::getx() {
    return this -> x;
}

float Camera::gety() {
    return this -> y;
}

void Camera::setx(float xPos) {
    this -> x = xPos;
}

void Camera::sety(float yPos) {
    this -> y = yPos;
}

void Camera::displayPos() {
    std::cout << "Camera position: [" << this -> x << ", " << this -> y << "]" << std::endl;
}

float Camera::centerX(Entity &entity) {
    this -> x = entity.getx();
    return this -> x;
}