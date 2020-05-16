#pragma once

#include "mapEvent.hpp"

class EventList {
public:
    EventList(int *map);
    void addEvent(int x, int y, int event);
    void pollList();
    void removeEvent();
    MapEvent *getHead();
    MapEvent *getTail();
private:
    MapEvent *head, *tail;
    int *mapReference;
};