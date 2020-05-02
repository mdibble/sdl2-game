#include "map.hpp"
#include "entity.hpp"
#include "camera.hpp"
#include <iostream>

#define RENDER 48

Map::Map(int reference[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++)
            this -> tileMap[i][j] = reference[i][j];
}

void Map::loadMap(RenderWindow &window, Camera &cam, SDL_Texture *palette) {
    float xPos = 0;
    float yPos = 0;
    Entity entity(xPos, yPos, palette);
    entity.setSpriteSrc(0, 0, 16, 16);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            entity.setx(i*RENDER);
            entity.sety(j*RENDER);
            if (this -> tileMap[j][i] == 1) {
                window.render(entity, cam);
            }
        }
    }
}