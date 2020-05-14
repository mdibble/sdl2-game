#include "map.hpp"
#include "entity.hpp"
#include "camera.hpp"
#include <iostream>

#define RENDER 48

Map::Map(int reference[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            this -> tileMap[i][j] = reference[i][j];
}

void Map::loadMap(RenderWindow &window, Camera &cam, SDL_Texture *palette) {
    float xPos = 0;
    float yPos = 0;
    Entity entity(xPos, yPos, palette);
    entity.setSpriteSrc(0, 0, 16, 16);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            entity.setx(i * RENDER);
            entity.sety(j * RENDER);
            switch (this -> tileMap[j][i]) {
                case 1:
                    entity.setSpriteSrc(0, 0, 16, 16);
                    window.render(entity, cam);
                    break;
                case 2:
                    entity.setSpriteSrc(16, 0, 16, 16);
                    window.render(entity, cam);
                    break;
                case 6:
                    entity.setSpriteSrc(0, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 7:
                    entity.setSpriteSrc(16, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 8:
                    entity.setSpriteSrc(0, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case 9:
                    entity.setSpriteSrc(16, 128, 16, 16);
                    window.render(entity, cam);
                    break;

            }
        }
    }
}