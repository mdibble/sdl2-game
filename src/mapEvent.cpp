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
    this -> finished = false;
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

void MapEvent::setPrevEvent(MapEvent *event) {
    this -> prevEvent = event;
}

int MapEvent::getX() {
    return this -> tileX;
}

int MapEvent::getY() {
    return this -> tileY;
}

bool MapEvent::getfinished() {
    return this -> finished;
}

MapEvent *MapEvent::getNextEvent() {
    return this -> nextEvent;
}

MapEvent *MapEvent::getPrevEvent() {
    return this -> prevEvent;
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
        return frame * 2;
    if (frame < 10)
        return 20 - frame * 2;
    finished = true;
    return 0;
}

int MapEvent::breakBlock() {
    *(this -> map + (MAP_WIDTH * this -> getY()) + this -> getX()) = '0';
    finished = true;
    return 0;
}

int MapEvent::questionBlockHit() {
    *(this -> map + (MAP_WIDTH * this -> getY()) + this -> getX()) = '5';
    if (frame < 5)
        return frame * 2;
    if (frame < 10)
        return 20 - frame * 2;
    finished = true;
    return 0;
}