#pragma once

#define MAP_WIDTH 256
#define MAP_HEIGHT 15

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderWindow.hpp"
#include "mapEvent.hpp"
#include "eventList.hpp"

class Map {
public:
    Map(int reference[MAP_HEIGHT][MAP_WIDTH]);
    Map(int *reference);
    void loadMap(RenderWindow &window, Camera &cam, SDL_Texture *palette, EventList *eventList);
    void drawMap();
private:
    int tileMap[MAP_HEIGHT][MAP_WIDTH];
    int *tileMapPointer;
};