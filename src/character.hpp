#pragma once

#include "entity.hpp"

class Character: public Entity {
public:
    Character(float xPos, float yPos, SDL_Texture* textSrc);
    void jump(float height);
    void updateVelocity();
    void move();
    float getvelocityX();
    float getvelocityY();
    bool getcanJump();
    bool getcollisionLeft();
    bool getcollisionRight();
    bool getcollisionTop();
    bool getcollisionBottom();
    void setvelocityX(float velocity);
    void setvelocityY(float velocity);
    void setcanJump(bool state);
    void setcollisionLeft(bool state);
    void setcollisionRight(bool state);
    void setcollisionTop(bool state);
    void setcollisionBottom(bool state);
    void pollTiles(bool debug);
    bool collision(int *map);
    void inBounds();
    
private:
    float velocityX, velocityY;
    float prevVelocityX, prevVelocityY; // deal with this!
    bool canJump;
    bool collisionLeft, collisionRight, collisionTop, collisionBottom;
    int tiles[8][2];
};