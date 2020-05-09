#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
    Entity(float xPos, float yPos, SDL_Texture* textSrc);
    float getx();
    float gety();
    float getvelocityX();
    float getvelocityY();
    SDL_Texture* gettexture();
    SDL_Rect getcurrentFrame();
    void setSpriteSrc(int x, int y, int w, int h);
    void move(float xPos, float yPos);
    void jump(float height);
    void updateLocation();
    void setx(float xPos);
    void sety(float yPos);
    void pollTiles(bool debug);
    bool collision(int map[15][15]);
    bool collision(int *map);
private:
    float x, y;
    float velocityX, velocityY;
    int tiles[4][2];
    SDL_Rect currentFrame;
    SDL_Texture *texture;
};