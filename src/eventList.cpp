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
    MapEvent *newEvent = new MapEvent(x, y, event, mapReference);

    if (this -> head == NULL) {
        this -> head = newEvent;
        this -> tail = newEvent;
    }

    else {
        this -> tail -> setNextEvent(newEvent);
        this -> tail = tail -> getNextEvent();
    }   
}

void EventList::pollList() {
    MapEvent *ptr = this -> head;
    while (ptr) {
        ptr -> progressEvent();
        ptr = ptr -> getNextEvent();
    }
}