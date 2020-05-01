#define SPRITE_SCALE 3

#include <iostream>
#include "renderwindow.hpp"
#include "entity.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
        std::cout << "Window failed to initialize: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::close() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &entity, Camera &camera) {

    SDL_Rect source;
    source.x = entity.getcurrentFrame().x;
    source.y = entity.getcurrentFrame().y;
    source.w = entity.getcurrentFrame().w;
    source.h = entity.getcurrentFrame().h;

    SDL_Rect dest;
    dest.x = entity.getx() - camera.getx();
    dest.y = entity.gety() + camera.gety();
    dest.w = entity.getcurrentFrame().w * SPRITE_SCALE;
    dest.h = entity.getcurrentFrame().h * SPRITE_SCALE;

    SDL_RenderCopy(renderer, entity.gettexture(), &source, &dest);
}

void RenderWindow::render(Entity &entity) {

    SDL_Rect source;
    source.x = entity.getcurrentFrame().x;
    source.y = entity.getcurrentFrame().y;
    source.w = entity.getcurrentFrame().w;
    source.h = entity.getcurrentFrame().h;

    SDL_Rect dest;
    dest.x = entity.getx();
    dest.y = entity.gety();
    dest.w = 1280;
    dest.h = 720;

    SDL_RenderCopy(renderer, entity.gettexture(), &source, &dest);
}

void RenderWindow::draw() {
    
    SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, path);

    if (!texture)
        std::cout << "Texture failed to load: " << SDL_GetError() << std::endl;

    return texture;
}