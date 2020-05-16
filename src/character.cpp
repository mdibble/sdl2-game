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

float Character::getvelocityX() {
    return (this -> velocityX);
}

float Character::getvelocityY() {
    return (this -> velocityY);
}

bool Character::getcanJump() {
    return (this -> canJump);
}

bool Character::getrunning() {
    return (this -> running);
}

bool Character::getcollisionLeft() {
    return (this -> collisionLeft);
}

bool Character::getcollisionRight() {
    return (this -> collisionRight);
}

bool Character::getcollisionTop() {
    return (this -> collisionTop);
}

bool Character::getcollisionBottom() {
    return (this -> collisionBottom);
}

void Character::setvelocityX(float velocity) {
    this -> velocityX = velocity;
}

void Character::setvelocityY(float velocity) {
    this -> velocityY = velocity;
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
    }
}

void Character::setcollisionBottom(bool state) {
    this -> collisionBottom = state;
}

void Character::setcollisionTop(bool state) {
    this -> collisionTop = state;
}

void Character::setcollisionLeft(bool state) {
    this -> collisionLeft = state;
}

void Character::setcollisionRight(bool state) {
    this -> collisionRight = state;
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

void Character::pollTiles(bool debug) {
    // Top Left
    this -> tiles[0][0] = (this -> x) / 48;
    this -> tiles[0][1] = (this -> y) / 48;

    // Top Right
    this -> tiles[1][0] = (this -> x + (this -> width - 2)) / 48;
    this -> tiles[1][1] = (this -> y) / 48;

    // Bottom Left
    this -> tiles[2][0] = (this -> x) / 48;
    this -> tiles[2][1] = (this -> y + (this -> height - 2)) / 48;

    // Bottom Right
    this -> tiles[3][0] = (this -> x + (this -> width - 2)) / 48;
    this -> tiles[3][1] = (this -> y + (this -> height - 2)) / 48;

    // Top Middle
    this -> tiles[4][0] = (this -> x + ((this -> width) / 2)) / 48;
    this -> tiles[4][1] = (this -> y) / 48;

    // Right Middle
    this -> tiles[5][0] = (this -> x + (this -> width - 2)) / 48;
    this -> tiles[5][1] = (this -> y + ((this -> height) / 2)) / 48;

    // Bottom Middle
    this -> tiles[6][0] = (this -> x + ((this -> width) / 2)) / 48;
    this -> tiles[6][1] = (this -> y + (this -> height - 2)) / 48;

    // Left Middle
    this -> tiles[7][0] = (this -> x) / 48;
    this -> tiles[7][1] = (this -> y + ((this -> height) / 2)) / 48;

    if (debug) {
        std::cout << "T-LEFT: " << this -> tiles[0][0] << ", " << this -> tiles[0][1] <<
                 " T-MIDDLE: " << this -> tiles[4][0] << ", " << this -> tiles[4][1] <<
                 " T-RIGHT: " << this -> tiles[1][0] << ", " << this -> tiles[1][1] <<
                 " B-LEFT: " << this -> tiles[2][0] << ", " << this -> tiles[2][1] <<
                 " B-MIDDLE: " << this -> tiles[6][0] << ", " << this -> tiles[6][1] <<
                 " B-RIGHT: " << this -> tiles[3][0] << ", " << this -> tiles[3][1] << 
                 " L-MIDDLE: " << this -> tiles[7][0] << ", " << this -> tiles[7][1] << 
                 " R-MIDDLE: " << this -> tiles[5][0] << ", " << this -> tiles[5][1] << std::endl;
    }
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
        clipped[i] =   (*(map + (MAP_WIDTH * this -> tiles[i][1]) + this -> tiles[i][0]) != '0' && 
                        (*(map + (MAP_WIDTH * this -> tiles[i][1]) + this -> tiles[i][0]) < 'a' ||
                        *(map + (MAP_WIDTH * this -> tiles[i][1]) + this -> tiles[i][0]) > 'z')) ? true : false;

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
        if (this -> status == 1 && *(map + (MAP_WIDTH * this -> tiles[4][1]) + this -> tiles[4][0]) == '2')
            eventList -> addEvent(this -> tiles[4][0], this -> tiles[4][1], 1);
        else if (*(map + (MAP_WIDTH * this -> tiles[4][1]) + this -> tiles[4][0]) == '2')
            eventList -> addEvent(this -> tiles[4][0], this -> tiles[4][1], 0);
        else if (*(map + (MAP_WIDTH * this -> tiles[4][1]) + this -> tiles[4][0]) == '3') {
            eventList -> addEvent(this -> tiles[4][0], this -> tiles[4][1], 2);
        }
    }

    if (this -> getcollisionLeft() || this -> getcollisionRight() || this -> getcollisionBottom() || this -> getcollisionTop())
        return true;
       
    return false;
}

void Character::inBounds() {
    if (this -> getcollisionLeft())
        this -> setx(this -> getx() + 1);
    if (this -> getcollisionRight())
        this -> setx(this -> getx() - 1);
    if (this -> getcollisionTop())
        this -> sety(this -> gety() + 1);
    if (this -> getcollisionBottom())
        this -> sety(this -> gety() - 1);
}