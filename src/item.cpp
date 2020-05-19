#include "item.hpp"
#include "map.hpp"

Item::Item(int tileX, int tileY, int itemID, SDL_Texture* textSrc) {
    this -> originTileX = tileX;
    this -> originTileY = tileY;
    this -> x = originTileX * 48.0;
    this -> y = originTileY * 48.0;

    this -> velocityY = 0;
    this -> velocityX = 0;

    this -> collisionBottom = false;
    this -> collisionTop = false;
    this -> collisionLeft = false;
    this -> collisionRight = false;

    this -> width = 48;
    this -> height = 48;

    this -> texture = textSrc;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;

    this -> itemID = itemID;

    switch (itemID) {
        case 0:
            this -> setSpriteSrc(0, 96, 16, 16);
            break;
        case 1:
            this -> setSpriteSrc(0, 0, 16, 16);
            this -> velocityX = 2;
            break;
        case 2:
            this -> setSpriteSrc(0, 32, 16, 16);
            break;
        case 3:
            this -> setSpriteSrc(16, 0, 16, 16);
            this -> velocityX = 2;
            break;
        case 4:
            this -> setSpriteSrc(0, 48, 16, 16);
            this -> velocityX = 2;
            break;
    }
}

void Item::setNextItem(Item *event) {
    this -> nextItem = event;
}

Item *Item::getNextItem() {
    return this -> nextItem;
}

void Item::move() {
    this -> x += this -> velocityX;
    this -> y += this -> velocityY;
}

bool Item::collision(int *map) {
    bool clipped[8];

    for (int i = 0; i < 8; i++)
        clipped[i] =   (*(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) != '0' && 
                        (*(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) < 'a' ||
                        *(map + (MAP_WIDTH * this -> currentTiles[i][1]) + this -> currentTiles[i][0]) > 'z')) ? true : false;

    bool L, R, B, T;

    L = (clipped[7] && (clipped[2] || clipped[0])) ? true : false;
    R = (clipped[5] && (clipped[1] || clipped[3])) ? true : false;
    T = (clipped[4] && (clipped[0] || clipped[1])) ? true : false;
    B = (clipped[6] && (clipped[2] || clipped[3])) ? true : false;

    if (L || R)
        this -> setvelocityX(this -> getvelocityX() * -1);

    if (B)
        this -> setvelocityY(0);

    this -> setcollisionLeft(L);
    this -> setcollisionRight(R);
    this -> setcollisionTop(T);
    this -> setcollisionBottom(B);

    if (this -> getcollisionLeft() || this -> getcollisionRight() || this -> getcollisionBottom() || this -> getcollisionTop())
        return true;
       
    return false;
}

void Item::updateEntity(int *map, Character *character) {
    this -> move();
    if (this -> itemID != 0 && this -> itemID != 2)
        this -> velocityY = this -> velocityY + 0.2;
    this -> pollTiles(false);
    if (this -> collision(map)) {
        while (this -> collision(map)) {
            this -> inBounds();
            this -> pollTiles(false);
        }
    }
    if (this -> checkInteraction(character))
        this -> consume(character);
}

void Item::consume(Character *effectOffload) {
    switch (this -> itemID) {
        case 0:
            break;
        case 1:
            effectOffload -> updateStatus(1);
            break;
        case 2:
            effectOffload -> updateStatus(2);
            break;
    }
}