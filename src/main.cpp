#define MOVE_INCREMENT 16
#define FRAMERATE 60

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderWindow.hpp"
#include "entity.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "character.hpp"
#include "controller.hpp"

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL2 Initialization Failed: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "SDL2_Image Initialization Failed: " << SDL_GetError() << std::endl;

    RenderWindow window("sdl2-game", 1280, 720);

    SDL_Texture* general = window.loadTexture("assets/images/general.png");
    SDL_Texture* character = window.loadTexture("assets/images/character.png");
    // must allow map to work for non-square arrays
    int reference[MAP_HEIGHT][MAP_WIDTH] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    Camera cam(0, 0);

    Entity sky(0, 0, general);
    sky.setSpriteSrc(50, 330, 1, 1);

    Character mario(40, 40, character);
    mario.setSpriteSrc(80, 34, 16, 16);

    Controller controller(0);
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
            controller.pollInputs(event);
        }

        if (controller.getB())
            mario.setrunning(true);
        else
            mario.setrunning(false);

        if (controller.getL() && controller.getR())
            mario.setvelocityX(mario.getvelocityX() / 1.2);

        else if (controller.getL())
            mario.setvelocityX(mario.getvelocityX() - 1);

        else if (controller.getR())
            mario.setvelocityX(mario.getvelocityX() + 1);

        else
            mario.setvelocityX(mario.getvelocityX() / 1.2);

        if (controller.getA())
            mario.jump(-15);

        mario.updateVelocity();
        mario.move();
        
        mario.pollTiles(false);
        if (mario.collision(&reference[0][0])) {
            while (mario.collision(&reference[0][0])) {
                mario.inBounds();
                mario.pollTiles(false);
            }
        }

        window.clear();
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