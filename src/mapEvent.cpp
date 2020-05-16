#include <iostream>

#include "mapEvent.hpp"
#include "map.hpp"

MapEvent::MapEvent(int x, int y, int event, int *mapPointer) {
    this -> frame = 0;
    this -> tileX = x;
    this -> tileY = y;
    this -> eventID = event;
    this -> map = mapPointer;
    this -> nextEvent = NULL;
    this -> length = (event == 0 || event == 2) ? 10 : 1; 
}

void MapEvent::setX(int x) {
    this -> tileX = x;
}

void MapEvent::setY(int y) {
    this -> tileY = y;
}

void MapEvent::setNextEvent(MapEvent *event) {
    this -> nextEvent = event;
}

int MapEvent::getX() {
    return this -> tileX;
}

int MapEvent::getY() {
    return this -> tileY;
}

MapEvent *MapEvent::getNextEvent() {
    return this -> nextEvent;
}

int MapEvent::progressEvent() {

    if (this -> frame >= this -> length)
        return 0;
    
    this -> frame++;
    
    switch (this -> eventID) {
        case 0:
            return this -> bump();
        case 1:
            return this -> breakBlock();
        case 2:
            return this -> questionBlockHit();
    }
    return -1;
}

int MapEvent::bump() {
    if (frame < 5)
        return frame;
    if (frame < 10)
        return 10 - frame;
    else
        return 0;
}

int MapEvent::breakBlock() {
    *(this -> map + (MAP_WIDTH * this -> getY()) + this -> getX()) = '0';
    return 0;
}

int MapEvent::questionBlockHit() {
    if (frame < 5)
        return frame;
    if (frame < 10)
        return 10 - frame;
    if (frame == 10)
        *(this -> map + (MAP_WIDTH * this -> getY()) + this -> getX()) = '5';
        return 0;
}