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
                case '1':
                    entity.setSpriteSrc(0, 0, 16, 16);
                    window.render(entity, cam);
                    break;
                case '2':
                    entity.setSpriteSrc(16, 0, 16, 16);
                    window.render(entity, cam);
                    break;
                case '3':
                    if (cam.getframe() % 60 < 15)
                        entity.setSpriteSrc(384, 0, 16, 16);
                    else if (cam.getframe() % 60 < 30)
                        entity.setSpriteSrc(400, 0, 16, 16);
                    else if (cam.getframe() % 60 < 45)
                        entity.setSpriteSrc(416, 0, 16, 16);
                    else
                        entity.setSpriteSrc(400, 0, 16, 16);
                    window.render(entity, cam);
                    break;
                case '4':
                    entity.setSpriteSrc(0, 16, 16, 16);
                    window.render(entity, cam);
                    break;
                case '6':
                    entity.setSpriteSrc(0, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case '7':
                    entity.setSpriteSrc(16, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case '8':
                    entity.setSpriteSrc(0, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case '9':
                    entity.setSpriteSrc(16, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'a':
                    entity.setSpriteSrc(176, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'b':
                    entity.setSpriteSrc(192, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'c':
                    entity.setSpriteSrc(208, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'd':
                    entity.setSpriteSrc(128, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'e':
                    entity.setSpriteSrc(144, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'f':
                    entity.setSpriteSrc(160, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'g':
                    entity.setSpriteSrc(144, 128, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'h':
                    entity.setSpriteSrc(128, 144, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'i':
                    entity.setSpriteSrc(0, 320, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'j':
                    entity.setSpriteSrc(16, 320, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'k':
                    entity.setSpriteSrc(32, 320, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'l':
                    entity.setSpriteSrc(0, 336, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'm':
                    entity.setSpriteSrc(16, 336, 16, 16);
                    window.render(entity, cam);
                    break;
                case 'n':
                    entity.setSpriteSrc(32, 336, 16, 16);
                    window.render(entity, cam);
                    break;

            }
        }
    }
}