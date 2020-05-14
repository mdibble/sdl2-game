#include <iostream>
#include <SDL2/SDL.h>

#include "controller.hpp"

Controller::Controller(int test) {
    this -> A = false;
    this -> B = false;
    this -> L = false;
    this -> R = false;
}

bool Controller::getA() {
    return this -> A;
}

bool Controller::getB() {
    return this -> B;
}

bool Controller::getL() {
    return this -> L;
}

bool Controller::getR() {
    return this -> R;
}

void Controller::pollInputs(SDL_Event &event) {

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                this -> L = true;
                break;
            case SDLK_RIGHT:
                this -> R = true;
                break;
            case SDLK_z:
                this -> B = true;
                break;
            case SDLK_x:
                this -> A = true;
                break;
        }
    }   

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                this -> L = false;
                break;
            case SDLK_RIGHT:
                this -> R = false;
                break;
            case SDLK_z:
                this -> B = false;
                break;
            case SDLK_x:
                this -> A = false;
                break;
        }
    }  
}