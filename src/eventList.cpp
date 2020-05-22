#include <iostream>

#include "eventList.hpp"

EventList::EventList(int *map) {
    this -> mapReference = map;
    this -> head = NULL;
    this -> tail = NULL;
}

MapEvent *EventList::getHead() {
    return this -> head;
}

MapEvent *EventList::getTail() {
    return this -> tail;
}

void EventList::addEvent(int x, int y, int event) {
    if (correspondingEvent(x, y))
        return;

    MapEvent *newEvent = new MapEvent(x, y, event, mapReference);
    newEvent -> setPrevEvent(this -> tail);
    newEvent -> setNextEvent(NULL);

    if (this -> head == NULL)
        this -> head = newEvent;
    else
        this -> tail -> setNextEvent(newEvent);
    this -> tail = newEvent;
}

void EventList::removeEvent(MapEvent *ptr) {
    if (ptr == NULL)  
        return;  
  
    if (head == ptr)  
        head = ptr -> getNextEvent();  

    if (ptr -> getNextEvent() != NULL)  
        ptr -> getNextEvent() -> setPrevEvent(ptr -> getPrevEvent());  

    if (ptr -> getPrevEvent() != NULL)  
        ptr -> getPrevEvent() -> setNextEvent(ptr -> getNextEvent()); 

    free(ptr);
}

void EventList::pollList() {
    MapEvent *ptr = this -> head;
    while (ptr) {
        ptr -> progressEvent();
        ptr = ptr -> getNextEvent();
    }
}

bool EventList::correspondingEvent(int x, int y) {
    MapEvent *ptr = this -> head;
    while (ptr) {
        if (ptr -> getX() == x && ptr -> getY() == y)
            return true;
        ptr = ptr -> getNextEvent();
    }
    return false;
}

void EventList::cleanList() {
    MapEvent *ptr = head;
    while (ptr) {
        if (ptr -> getfinished() == true)
            removeEvent(ptr);
        ptr = ptr -> getNextEvent();
    }
}