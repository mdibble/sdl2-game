#include "entity.hpp"

Entity::Entity(float xPos, float yPos, SDL_Texture* textSrc) {
    this -> x = xPos;
    this -> y = yPos;
    this -> texture = textSrc;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
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

SDL_Texture* Entity::gettexture() {
    return (this -> texture);
}

SDL_Rect Entity::getcurrentFrame() {
    return (this -> currentFrame);
}