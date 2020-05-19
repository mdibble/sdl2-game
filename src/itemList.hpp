#pragma once

#include "item.hpp"

class ItemList {
public:
    ItemList(int *map, Character *character);
    void addItem(int tileX, int tileY, int itemID, SDL_Texture* textSrc);
    void addEnemy();
    void pollList();
    void removeEntity();
    Item *getHead();
    Item *getTail();
private:
    Item *head, *tail;
    int *map;
    Character *character;
};

// have to deal with removing items from the data structure