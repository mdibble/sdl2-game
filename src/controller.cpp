#include <iostream>
#include <SDL2/SDL.h>

#include "controller.hpp"

Controller::Controller(int test) {
    this -> A = false;
    this -> B = false;
    this -> L = false;
    this -> R = false;
}

void Controller::pollInputs(SDL_Event &event) {
    
    this -> L = false;
    this -> R = false;
    this -> A = false;
    this -> B = false;

    if (event.type == SDL_KEYDOWN) {
        this -> L = (event.key.keysym.sym == SDLK_LEFT) ? true : false;
        this -> R = (event.key.keysym.sym == SDLK_RIGHT) ? true : false;
        this -> A = (event.key.keysym.sym == SDLK_z) ? true : false;
        this -> B = (event.key.keysym.sym == SDLK_x) ? true : false;
    }   
    std::cout << this -> L << this -> R << this -> A << this -> B << std::endl;
    // work in progress, have to figure out how to handle multiple inputs at once
}