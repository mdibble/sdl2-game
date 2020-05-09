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
    void setvelocityX(float velocity);
    void setvelocityY(float velocity);
    void pollTiles(bool debug);
    bool collision(int *map);
private:
    float velocityX, velocityY;
    float prevVelocityX, prevVelocityY; // deal with this
    int tiles[4][2];
};