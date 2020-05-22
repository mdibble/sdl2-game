#pragma once

#include "character.hpp"
#include <iostream>

class Item: public DynamicEntity {
public:
    Item(int tileX, int tileY, int itemID, SDL_Texture* textSrc);
    // Item IDs:
    // [0] Coin
    // [1] Mushroom
    // [2] Fire Flower
    // [3] 1-Up
    // [4] Star
    // [5] Coin (in question block)
    void updateEntity(int *map, Character *character, EventList *eventList);
    bool collision(int *map);
    void move();
    void consume(Character *effectOffload);
    void setNextItem(Item *item);
    void setPrevItem(Item *item);
    Item *getNextItem();
    Item *getPrevItem();
    bool getactive();
    int getquantity();
private:
    int itemID;
    int quantity;
    bool active;
    bool spawning;
    Item *nextItem;
    Item *prevItem;
};