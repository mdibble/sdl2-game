#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
    Entity(float xPos, float yPos, SDL_Texture* textSrc);
    float getx();
    float gety();
    SDL_Texture* gettexture();
    SDL_Rect getcurrentFrame();
    void setSpriteSrc(int x, int y, int w, int h);
private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture *texture;
};