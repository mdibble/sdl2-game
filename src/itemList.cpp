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
    newItem -> setPrevItem(this -> tail);
    newItem -> setNextItem(NULL);

    if (this -> head == NULL)
        this -> head = newItem;
    else
        this -> tail -> setNextItem(newItem);
    this -> tail = newItem;
}

void ItemList::removeItem(Item *ptr) {
    if (!ptr)
        return;

	if (ptr -> getPrevItem() == NULL) {
		head = ptr -> getNextItem();
        if (head)
		    head -> setPrevItem(NULL);
	}

	else if (ptr -> getNextItem() == NULL) {
		tail = ptr -> getPrevItem();
		tail -> setNextItem(NULL);
	}

	else {
		ptr -> getPrevItem() -> setNextItem(ptr -> getNextItem());
		ptr -> getNextItem() -> setPrevItem(ptr -> getPrevItem());
	}

	delete ptr;
}

bool ItemList::correspondingItem(int x, int y) {
    Item *ptr = this -> head;
    while (ptr) {
        if (ptr -> getoriginTileX() == x && ptr -> getoriginTileY() == y)
            return true;
        ptr = ptr -> getNextItem();
    }
    return false;
}

void ItemList::cleanList() {
    Item *ptr = head;
    while (ptr) {
        if (ptr -> getquantity() == 0) 
            removeItem(ptr);
        ptr = ptr -> getNextItem();
    }
}

void ItemList::pollList(EventList *events) {
    Item *ptr = this -> head;
    while (ptr) {
        ptr -> updateEntity(this -> map, this -> character, events);
        ptr = ptr -> getNextItem();
    }
    cleanList();
}