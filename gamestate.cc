#include "gamestate.h"

bool GameState::update() {
    if (floor.update(*this))
        return true;
    return jumpy.update(*this);
}

void GameState::draw() {
    floor.draw();
    jumpy.draw();
}
