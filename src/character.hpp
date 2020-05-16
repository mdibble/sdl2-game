#pragma once

#include "entity.hpp"
#include "eventList.hpp"

class Character: public Entity {
public:
    Character(float xPos, float yPos, SDL_Texture* textSrc);
    void jump(float height);
    void updateVelocity();
    void move();
    void updateStatus(int update);
    float getvelocityX();
    float getvelocityY();
    bool getcanJump();
    bool getrunning();
    bool getcollisionLeft();
    bool getcollisionRight();
    bool getcollisionTop();
    bool getcollisionBottom();
    void setvelocityX(float velocity);
    void setvelocityY(float velocity);
    void setcanJump(bool state);
    void setrunning(bool state);
    void setcollisionLeft(bool state);
    void setcollisionRight(bool state);
    void setcollisionTop(bool state);
    void setcollisionBottom(bool state);
    void pollTiles(bool debug);
    bool collision(int *map, EventList *eventList, bool enableEvents);
    void inBounds();
    
private:
    float velocityX, velocityY;
    bool canJump, running;
    bool collisionLeft, collisionRight, collisionTop, collisionBottom;
    int tiles[8][2];
    int status;
    int width, height;
};