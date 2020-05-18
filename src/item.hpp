#pragma once

#include "dynamicEntity.hpp"
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
    void updateEntity(int *map);
    bool collision(int *map);
    void move();
    void checkInteraction(Character &character);
    void consume();
private:
    int itemID;
    int quantity;
};