#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class Camera {
public: 
    Camera(float xPos, float yPos);
    float getx();
    float gety();
    Uint32 getframe();
    void setx(float xPos);
    void sety(float yPos);
    void setframe(Uint32 amount);
    void displayPos();
    float centerX(Entity &entity);
private:
    float x, y;
    Uint32 frame;
};