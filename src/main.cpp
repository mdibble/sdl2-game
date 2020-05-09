#define MOVE_INCREMENT 16
#define FRAMERATE 60

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderWindow.hpp"
#include "entity.hpp"
#include "camera.hpp"
#include "map.hpp"

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL2 Initialization Failed: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "SDL2_Image Initialization Failed: " << SDL_GetError() << std::endl;

    RenderWindow window("sdl2-game", 1280, 720);

    SDL_Texture* general = window.loadTexture("assets/images/general.png");
    SDL_Texture* character = window.loadTexture("assets/images/character.png");

    int reference[MAP_WIDTH][MAP_HEIGHT] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
                                            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


    Camera cam(0, 0);

    Entity sky(0, 0, general);
    sky.setSpriteSrc(50, 330, 1, 1);

    Entity mario(0, 0, character);
    mario.setSpriteSrc(80, 34, 16, 16);

    Map map(reference);

    Uint32 frameStart;
    int frameTime;

    bool gameLoop = true;
    SDL_Event event;

    while (gameLoop) {

        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameLoop = false;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // cam.setx(cam.getx() - 10);
                        mario.setx(mario.getx() - 10);
                        break;
                    case SDLK_RIGHT:
                        // cam.setx(cam.getx() + 10);
                        mario.setx(mario.getx() + 10);
                        break;
                    case SDLK_UP:
                        // cam.sety(cam.gety() + 10);
                        mario.sety(mario.gety() - 10);
                        break;
                    case SDLK_DOWN:
                        // cam.sety(cam.gety() - 10);
                        mario.sety(mario.gety() + 10);
                        
                        break;
                }
            }
        }

        window.clear();
        
        mario.pollTiles(false);
        if (mario.collision(&reference[0][0])) {
            std::cout << "Clipped" << std::endl;
            // testing
            while (mario.collision(&reference[0][0])) {
                mario.sety(mario.gety() - 1);
                mario.pollTiles(true);
            }
                
        }
            

        cam.centerX(mario);
        window.render(sky);
        map.loadMap(window, cam, general);
        window.render(mario, cam);
        window.draw();

        frameTime = SDL_GetTicks() - frameStart;
        if ((1000 / FRAMERATE) > frameTime)
            SDL_Delay((1000 / FRAMERATE) - frameTime);
    }

    window.close();
    SDL_Quit();
    return 0;
}