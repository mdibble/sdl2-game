#include "character.hpp"
#include "map.hpp"
#include <iostream>

Character::Character(float xPos, float yPos, SDL_Texture* textSrc) {
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

float Character::getvelocityX() {
    return (this -> velocityX);
}

float Character::getvelocityY() {
    return (this -> velocityY);
}

void Character::setvelocityX(float velocity) {
    this -> velocityX = velocity;
}

void Character::setvelocityY(float velocity) {
    this -> velocityY = velocity;
}

void Character::updateVelocity() {
    this -> velocityY = this -> velocityY + 0.5;
}

void Character::move() {
    this -> x += this -> velocityX;
    this -> y += this -> velocityY;
};

void Character::pollTiles(bool debug) {
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

bool Character::collision(int *map) {

    for (int i = 0; i < 4; i++)
        if (*(map + (MAP_WIDTH * this -> tiles[i][1]) + this -> tiles[i][0]) != 0)
            return true;
       
    return false;
}