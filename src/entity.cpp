#include "entity.hpp"
#include "map.hpp"
#include <iostream>

Entity::Entity(float xPos, float yPos, SDL_Texture* textSrc) {
    this -> x = xPos;
    this -> y = yPos;
    this -> texture = textSrc;

    this -> velocityY = 0;
    this -> velocityX = 0;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

void Entity::move(float xPos, float yPos) {
    this -> x = xPos;
    this -> y = yPos;
}

void Entity::jump(float height) {
    this -> velocityY = height;
}

void Entity::updateLocation() {
    this -> move((this -> x) + velocityX, (this -> y) - velocityY);

    velocityY -= 0.1 + (velocityY*0.1);
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

float Entity::getvelocityX() {
    return (this -> velocityX);
}

float Entity::getvelocityY() {
    return (this -> velocityY);
}

void Entity::pollTiles(bool debug) {
    this -> tiles[0][0] = (this -> x) / 48;
    this -> tiles[0][1] = (this -> y) / 48;

    this -> tiles[1][0] = (this -> x + 48) / 48;
    this -> tiles[1][1] = (this -> y) / 48;

    this -> tiles[2][0] = (this -> x) / 48;
    this -> tiles[2][1] = (this -> y + 48) / 48;

    this -> tiles[3][0] = (this -> x + 48) / 48;
    this -> tiles[3][1] = (this -> y + 48) / 48;

    if (debug) {
        std::cout << "T-LEFT: " << this -> tiles[0][0] << ", " << this -> tiles[0][1] <<
                 " T-RIGHT: " << this -> tiles[1][0] << ", " << this -> tiles[1][1] <<
                 " B-LEFT: " << this -> tiles[2][0] << ", " << this -> tiles[2][1] <<
                 " B-RIGHT: " << this -> tiles[3][0] << ", " << this -> tiles[3][1] << std::endl;
    }
}

bool Entity::collision(int map[MAP_WIDTH][MAP_WIDTH]) {

    for (int i = 0; i < 4; i++)
        if (map[this -> tiles[i][1]][this -> tiles[i][0]] != 0)
            return true;
       
    return false;
}

bool Entity::collision(int *map) {

    for (int i = 0; i < 4; i++)
        if (*(map + (MAP_WIDTH * this -> tiles[i][1]) + this -> tiles[i][0]) != 0)
            return true;
       
    return false;
}

SDL_Texture* Entity::gettexture() {
    return (this -> texture);
}

SDL_Rect Entity::getcurrentFrame() {
    return (this -> currentFrame);
}