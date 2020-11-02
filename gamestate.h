#ifndef GAME_STATE
#define GAME_STATE

#include "floor.h"
#include "jumpy.h"

class GameState {
public:
    Floor floor;
    Jumpy jumpy;
    virtual bool update();
    virtual void draw();
};

#endif
