#ifndef GAME_STATE
#define GAME_STATE

#include <cstdint>

#include "floor.h"
#include "jumpy.h"

class GameState {
public:
    Floor floor;
    Jumpy jumpy;
    uint64_t tick = 0;
    virtual bool update();
    virtual void draw();
};

#endif
