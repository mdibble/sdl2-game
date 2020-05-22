#pragma once

#include "item.hpp"

class ItemList {
public:
    ItemList(int *map, Character *character);
    void addItem(int tileX, int tileY, int itemID, SDL_Texture* textSrc);
    void addEnemy();
    void pollList(EventList *events);
    void removeItem(Item *ptr);
    bool correspondingItem(int x, int y);
    void cleanList();
    Item *getHead();
    Item *getTail();
private:
    Item *head, *tail;
    int *map;
    Character *character;
};