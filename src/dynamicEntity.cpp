#include "dynamicEntity.hpp"
#include "map.hpp"
#include <iostream>

DynamicEntity::DynamicEntity(int tileX, int tileY, SDL_Texture* textSrc) {
    this -> originTileX = tileX;
    this -> originTileY = tileY;
    this -> x = originTileX * 48.0;
    this -> y = originTileY * 48.0;
    this -> texture = textSrc;

    this -> velocityY = 0;
    this -> velocityX = 0;

    this -> collisionBottom = false;
    this -> collisionTop = false;
    this -> collisionLeft = false;
    this -> collisionRight = false;

    this -> width = 48;
    this -> height = 48;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

DynamicEntity::DynamicEntity() {

}

void DynamicEntity::updateEntity() {
    std::cout << "Entity updated // This should ALWAYS be overridden" << std::endl;
}

float DynamicEntity::getvelocityX() {
    return (this -> velocityX);
}

float DynamicEntity::getvelocityY() {
    return (this -> velocityY);
}

int DynamicEntity::getoriginTileX() {
    return (this -> originTileX);
}

int DynamicEntity::getoriginTileY() {
    return (this -> originTileY);
}

int DynamicEntity::getwidth() {
    return this -> width;
}

int DynamicEntity::getheight() {
    return this -> height;
}

bool DynamicEntity::getcollisionLeft() {
    return (this -> collisionLeft);
}

bool DynamicEntity::getcollisionRight() {
    return (this -> collisionRight);
}

bool DynamicEntity::getcollisionTop() {
    return (this -> collisionTop);
}

bool DynamicEntity::getcollisionBottom() {
    return (this -> collisionBottom);
}

void DynamicEntity::setvelocityX(float velocity) {
    this -> velocityX = velocity;
}

void DynamicEntity::setvelocityY(float velocity) {
    this -> velocityY = velocity;
}

void DynamicEntity::setoriginTileX(int tile) {
    this -> originTileX = tile;
}

void DynamicEntity::setoriginTileY(int tile) {
    this -> originTileY = tile;
}

void DynamicEntity::setwidth(int newWidth) {
    this -> width = newWidth;
}

void DynamicEntity::setheight(int newHeight) {
    this -> height = newHeight;
}

void DynamicEntity::setcollisionBottom(bool state) {
    this -> collisionBottom = state;
}

void DynamicEntity::setcollisionTop(bool state) {
    this -> collisionTop = state;
}

void DynamicEntity::setcollisionLeft(bool state) {
    this -> collisionLeft = state;
}

void DynamicEntity::setcollisionRight(bool state) {
    this -> collisionRight = state;
}

void DynamicEntity::pollTiles(bool debug) {
    // Top Left
    this -> currentTiles[0][0] = (this -> x) / 48;
    this -> currentTiles[0][1] = (this -> y) / 48;

    // Top Right
    this -> currentTiles[1][0] = (this -> x + (this -> width - 2)) / 48;
    this -> currentTiles[1][1] = (this -> y) / 48;

    // Bottom Left
    this -> currentTiles[2][0] = (this -> x) / 48;
    this -> currentTiles[2][1] = (this -> y + (this -> height - 2)) / 48;

    // Bottom Right
    this -> currentTiles[3][0] = (this -> x + (this -> width - 2)) / 48;
    this -> currentTiles[3][1] = (this -> y + (this -> height - 2)) / 48;

    // Top Middle
    this -> currentTiles[4][0] = (this -> x + ((this -> width) / 2)) / 48;
    this -> currentTiles[4][1] = (this -> y) / 48;

    // Right Middle
    this -> currentTiles[5][0] = (this -> x + (this -> width - 2)) / 48;
    this -> currentTiles[5][1] = (this -> y + ((this -> height) / 2)) / 48;

    // Bottom Middle
    this -> currentTiles[6][0] = (this -> x + ((this -> width) / 2)) / 48;
    this -> currentTiles[6][1] = (this -> y + (this -> height - 2)) / 48;

    // Left Middle
    this -> currentTiles[7][0] = (this -> x) / 48;
    this -> currentTiles[7][1] = (this -> y + ((this -> height) / 2)) / 48;

    if (debug) {
        std::cout << "T-LEFT: " << this -> currentTiles[0][0] << ", " << this -> currentTiles[0][1] <<
                 " T-MIDDLE: " << this -> currentTiles[4][0] << ", " << this -> currentTiles[4][1] <<
                 " T-RIGHT: " << this -> currentTiles[1][0] << ", " << this -> currentTiles[1][1] <<
                 " B-LEFT: " << this -> currentTiles[2][0] << ", " << this -> currentTiles[2][1] <<
                 " B-MIDDLE: " << this -> currentTiles[6][0] << ", " << this -> currentTiles[6][1] <<
                 " B-RIGHT: " << this -> currentTiles[3][0] << ", " << this -> currentTiles[3][1] << 
                 " L-MIDDLE: " << this -> currentTiles[7][0] << ", " << this -> currentTiles[7][1] << 
                 " R-MIDDLE: " << this -> currentTiles[5][0] << ", " << this -> currentTiles[5][1] << std::endl;
    }
}

bool DynamicEntity::collision(int *map) {

    //  0   4   1
    //
    //  7       5
    //         
    //  2   6   3

    // Left     7 and (2 or 0)
    // Right    5 and (1 or 3)
    // Top      4 and (0 or 1)
    // Bottom   6 and (2 or 3)

    bool clipped[8];

    for (int i = 0; i < 8; i++)
        clipped[i] =   (*(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) != '0' && 
                        (*(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) < 'a' ||
                        *(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) > 'z')) ? true : false;

    bool L, R, B, T;

    L = (clipped[7] && (clipped[2] || clipped[0])) ? true : false;
    R = (clipped[5] && (clipped[1] || clipped[3])) ? true : false;
    T = (clipped[4] && (clipped[0] || clipped[1])) ? true : false;
    B = (clipped[6] && (clipped[2] || clipped[3])) ? true : false;

    this -> setcollisionLeft(L);
    this -> setcollisionRight(R);
    this -> setcollisionTop(T);
    this -> setcollisionBottom(B);

    if (this -> getcollisionLeft() || this -> getcollisionRight() || this -> getcollisionBottom() || this -> getcollisionTop())
        return true;
       
    return false;
}

void DynamicEntity::inBounds() {
    if (this -> getcollisionLeft())
        this -> setx(this -> getx() + 1);
    if (this -> getcollisionRight())
        this -> setx(this -> getx() - 1);
    if (this -> getcollisionTop())
        this -> sety(this -> gety() + 1);
    if (this -> getcollisionBottom())
        this -> sety(this -> gety() - 1);
}

bool DynamicEntity::checkInteraction(DynamicEntity *that) {
    if ((this -> getx() >= that -> getx() && this -> getx() <= that -> getx() + that -> getwidth() || 
        (this -> getx() + this -> getwidth() >= that -> getx() && this -> getx()  + this -> getwidth() <= that -> getx() + that -> getwidth())) &&
        ((this -> gety() >= that -> gety() && this -> gety() <= that -> gety() + that -> getheight()) || 
        (this -> gety() + this -> getheight() >= that -> gety() && this -> gety()  + this -> getheight() <= that -> gety() + that -> getheight())))
        return true;
    return false;
}