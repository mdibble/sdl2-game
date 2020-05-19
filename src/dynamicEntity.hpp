#pragma once

#include "entity.hpp"

class DynamicEntity: public Entity {
public:
    DynamicEntity(int tileX, int tileY, SDL_Texture* textSrc);
    DynamicEntity();
    void updateEntity();
    float getvelocityX();
    float getvelocityY();
    int getoriginTileX();
    int getoriginTileY();
    int getwidth();
    int getheight();
    bool getcollisionLeft();
    bool getcollisionRight();
    bool getcollisionTop();
    bool getcollisionBottom();
    void setvelocityX(float velocity);
    void setvelocityY(float velocity);
    void setoriginTileX(int tile);
    void setoriginTileY(int tile);
    void setwidth(int width);
    void setheight(int height);
    void setcollisionLeft(bool state);
    void setcollisionRight(bool state);
    void setcollisionTop(bool state);
    void setcollisionBottom(bool state);
    void pollTiles(bool debug);
    bool collision(int *map);
    void inBounds();
    bool checkInteraction(DynamicEntity *entity);
protected:
    float velocityX, velocityY;
    int originTileX, originTileY;
    bool collisionLeft, collisionRight, collisionTop, collisionBottom;
    int width, height;
    int currentTiles[8][2];
};