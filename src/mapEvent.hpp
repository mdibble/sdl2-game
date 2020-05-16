#pragma once

class MapEvent {
public:
    MapEvent(int x, int y, int event, int *map);
    int progressEvent();
    int bump();
    int breakBlock();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setNextEvent(MapEvent *event);
    MapEvent *getNextEvent();

private:
    int frame, length;
    int tileX, tileY;
    int eventID;
    int *map;
    MapEvent *nextEvent;
};