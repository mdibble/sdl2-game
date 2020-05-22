#pragma once

class MapEvent {
public:
    MapEvent(int x, int y, int event, int *map);
    int progressEvent();
    int bump();
    int breakBlock();
    int questionBlockHit();
    int getX();
    int getY();
    bool getfinished();
    void setX(int x);
    void setY(int y);
    void setNextEvent(MapEvent *event);
    void setPrevEvent(MapEvent *event);
    MapEvent *getNextEvent();
    MapEvent *getPrevEvent();

private:
    int frame, length;
    int tileX, tileY;
    int eventID;
    int *map;
    bool finished;
    MapEvent *nextEvent;
    MapEvent *prevEvent;
};