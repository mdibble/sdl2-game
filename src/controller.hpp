#pragma once

class Controller {
public:
    Controller(int test);
    void pollInputs(SDL_Event &event);
    bool getA();
    bool getB();
    bool getL();
    bool getR();
private:
    bool A, B, L, R;
};