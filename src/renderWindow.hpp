#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "camera.hpp"

class RenderWindow {
public:
    RenderWindow(const char* title, int w, int h);
    SDL_Texture* loadTexture(const char* path);
    void close();
    void clear();
    void render(Entity &entity, Camera &camera);
    void render(Entity &entity);
    void draw();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};