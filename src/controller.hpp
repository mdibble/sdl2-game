#pragma once

class Controller {
public:
    Controller(int test);
    void pollInputs(SDL_Event &event);
private:
    bool A, B, L, R;
};