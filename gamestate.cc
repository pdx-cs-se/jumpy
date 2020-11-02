#include "gamestate.h"

bool GameState::update() {
    if (floor.update(*this))
        return true;
    auto jump = jumpy.update(*this);
    this->tick++;
    return jump;
}

void GameState::draw() {
    floor.draw();
    jumpy.draw();
}
