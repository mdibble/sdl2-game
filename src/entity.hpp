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
private:
    float x, y;
    float velocityX, velocityY;
    SDL_Rect currentFrame;
    SDL_Texture *texture;
};