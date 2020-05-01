#define CAM_INCREMENT 16

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderwindow.hpp"
#include "entity.hpp"
#include "camera.hpp"

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL2 Initialization Failed: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "SDL2_Image Initialization Failed: " << SDL_GetError() << std::endl;

    RenderWindow window("sdl2-game", 1280, 720);

    SDL_Texture* general = window.loadTexture("../assets/images/general.png");
    SDL_Texture* character = window.loadTexture("../assets/images/character.png");

    Camera cam(0, 0);
    Entity platform(0, 672, general);
    Entity platform2(48, 672, general);
    Entity sky(0, 0, general);
    Entity mario(16, 624, character);

    platform.setSpriteSrc(0, 0, 16, 16);
    platform2.setSpriteSrc(0, 0, 16, 16);
    mario.setSpriteSrc(80, 34, 16, 16);
    sky.setSpriteSrc(60, 340, 1, 1);

    bool gameLoop = true;
    SDL_Event event;

    while (gameLoop) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameLoop = false;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        cam.setx(cam.getx() - CAM_INCREMENT);
                        cam.displayPos();
                        break;
                    case SDLK_RIGHT:
                        cam.setx(cam.getx() + CAM_INCREMENT);
                        cam.displayPos();
                        break;
                    case SDLK_UP:
                        cam.sety(cam.gety() + CAM_INCREMENT);
                        cam.displayPos();
                        break;
                    case SDLK_DOWN:
                        cam.sety(cam.gety() - CAM_INCREMENT);
                        cam.displayPos();
                        break;
                }
            }
        }

        window.clear();
        window.render(sky);
        window.render(platform, cam);
        window.render(platform2, cam);
        window.render(mario, cam);
        window.draw();
        
    }

    window.close();
    SDL_Quit();
    return 0;
}