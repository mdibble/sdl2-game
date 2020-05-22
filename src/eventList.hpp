#pragma once

#include "mapEvent.hpp"

class EventList {
public:
    EventList(int *map);
    void addEvent(int x, int y, int event);
    void pollList();
    void cleanList();
    void removeEvent(MapEvent *event);
    bool correspondingEvent(int x, int y);
    MapEvent *getHead();
    MapEvent *getTail();
private:
    MapEvent *head, *tail;
    int *mapReference;
};

// have to deal with removing items from the data structure