#include "ncurses.h"

#include "floor.h"

Floor::Floor() {
    for (int i = 0; i < COLS; i++)
        tiles.push_back(floor_tile());
}

// Draw the current floor.
void Floor::draw(void) {
    for (int col = 0; col < COLS; col++)
        mvaddch(LINES - 1, col, tiles[col]);
}

// Returns true on game over.
bool Floor::update(GameState &state) {
    for (int col = 0; col < COLS - 1; col++)
        tiles[col] = tiles[col + 1];
    static uniform_real_distribution<float> distribution;
    if (distribution(generator) <= hole_prob)
        tiles[COLS - 1] = ' ';
    else
        tiles[COLS - 1] = floor_tile();
    return false;
}

bool Floor::on_space(void) {
    return tiles[1] == ' ';
}
