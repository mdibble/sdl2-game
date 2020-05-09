#include "entity.hpp"
#include "map.hpp"
#include <iostream>

Entity::Entity(float xPos, float yPos, SDL_Texture* textSrc) {
    this -> x = xPos;
    this -> y = yPos;
    this -> texture = textSrc;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

Entity::Entity() {
    
}

void Entity::setSpriteSrc(int x, int y, int w, int h) {
    this -> currentFrame.x = x;
    this -> currentFrame.y = y;
    this -> currentFrame.w = w;
    this -> currentFrame.h = h;
}

float Entity::getx() {
    return (this -> x);
}

float Entity::gety() {
    return (this -> y);
}

void Entity::setx(float xPos) {
    this -> x = xPos;
}

void Entity::sety(float yPos) {
    this -> y = yPos;
}

SDL_Texture* Entity::gettexture() {
    return (this -> texture);
}

SDL_Rect Entity::getcurrentFrame() {
    return (this -> currentFrame);
}