#pragma once

#include "dynamicEntity.hpp"
#include "eventList.hpp"

class Character: public DynamicEntity {
public:
    Character(float xPos, float yPos, SDL_Texture* textSrc);
    void jump(float height);
    void updateVelocity();
    void move();
    void updateStatus(int update);
    bool getcanJump();
    bool getrunning();
    int* gettiles();
    void setcanJump(bool state);
    void setrunning(bool state);
    bool collision(int *map, EventList *eventList, bool enableEvents);
    
private:
    bool canJump, running;
    int status;
};