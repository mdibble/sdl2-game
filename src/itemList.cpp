#include "itemList.hpp"

ItemList::ItemList(int *mapPtr, Character *characterPtr) {
    this -> head = NULL;
    this -> tail = NULL;
    this -> map = mapPtr;
    this -> character = characterPtr;
}

Item *ItemList::getHead() {
    return this -> head;
}

Item *ItemList::getTail() {
    return this -> tail;
}

void ItemList::addItem(int tileX, int tileY, int itemID, SDL_Texture* textSrc) {
    Item *newItem = new Item(tileX, tileY, itemID, textSrc);

    if (this -> head == NULL) {
        this -> head = newItem;
        this -> tail = newItem;
    }

    else {
        this -> tail -> setNextItem(newItem);
        this -> tail = tail -> getNextItem();
    }  
}

void ItemList::pollList() {
    Item *ptr = this -> head;
    while (ptr) {
        ptr -> updateEntity(this -> map, this -> character);
        ptr = ptr -> getNextItem();
    }
}