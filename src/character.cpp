#include "character.hpp"
#include "map.hpp"
#include <iostream>

Character::Character(float xPos, float yPos, SDL_Texture* textSrc) {
    this -> x = xPos;
    this -> y = yPos;
    this -> texture = textSrc;

    this -> velocityY = 0;
    this -> velocityX = 0;

    this -> collisionBottom = false;
    this -> collisionTop = false;
    this -> collisionLeft = false;
    this -> collisionRight = false;

    this -> canJump = true;
    this -> running = false;
    this -> status = 0;
    this -> width = 48;
    this -> height = 48;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

bool Character::getcanJump() {
    return (this -> canJump);
}

bool Character::getrunning() {
    return (this -> running);
}

void Character::setcanJump(bool state) {
    this -> canJump = state;
}

void Character::setrunning(bool state) {
    this -> running = state;
}

void Character::updateStatus(int update) {
    this -> status = update;

    switch (this -> status) {
        case 0:
            this -> width = 48;
            this -> height = 48;
            this -> setSpriteSrc(80, 34, 16, 16);
            break;
        case 1:
            this -> width = 48;
            this -> height = 96;
            this -> setSpriteSrc(80, 1, 16, 32);
            break;
        case 2:
            this -> width = 48;
            this -> height = 96;
            this -> setSpriteSrc(80, 129, 16, 32);
            break;
    }
}

void Character::updateVelocity() {
    this -> velocityY = this -> velocityY + 0.5;
    if (this -> velocityX > 5)
        this -> velocityX = 5;
    else if (this -> velocityX < -5)
        this -> velocityX = -5;
}

void Character::move() {
    this -> x += this -> velocityX;
    this -> y += this -> velocityY;
}

void Character::jump(float height) {
    if (this -> canJump)
        this -> setvelocityY(height);
    this -> setcanJump(false);
}

bool Character::collision(int *map, EventList *eventList, bool enableEvents) {

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

    if (L || R)
        this -> setvelocityX(0);

    if (B) {
        this -> setvelocityY(0);
        this -> setcanJump(true);
    }

    if (T)
        this -> setvelocityY(this -> getvelocityY() * -0.75);

    this -> setcollisionLeft(L);
    this -> setcollisionRight(R);
    this -> setcollisionTop(T);
    this -> setcollisionBottom(B);

    if (this -> getcollisionTop()) {
        if (this -> status == 1 && *(map + (MAP_WIDTH * this -> currentTiles[4][1]) + this -> currentTiles[4][0]) == '2')
            eventList -> addEvent(this -> currentTiles[4][0], this -> currentTiles[4][1], 1);
        else if (*(map + (MAP_WIDTH * this -> currentTiles[4][1]) + this -> currentTiles[4][0]) == '2')
            eventList -> addEvent(this -> currentTiles[4][0], this -> currentTiles[4][1], 0);
        else if (*(map + (MAP_WIDTH * this -> currentTiles[4][1]) + this -> currentTiles[4][0]) == '3') {
            eventList -> addEvent(this -> currentTiles[4][0], this -> currentTiles[4][1], 2);
        }
    }

    if (this -> getcollisionLeft() || this -> getcollisionRight() || this -> getcollisionBottom() || this -> getcollisionTop())
        return true;
       
    return false;
}