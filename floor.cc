#include <cassert>
#include <ncurses.h>

#include "floor.h"
#include "gamestate.h"

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
    // Update floor rate and accel; check for
    // move.
    this->floor_shift += this->floor_rate;
    this->floor_rate += FLOOR_ACCEL;
    if (this->floor_shift < 1.0)
        return false;

    // Find the integer part of the floor shift and adjust
    // it.
    int int_shift = floor(floor_shift);
    assert(int_shift > 0);
    this->floor_shift -= int_shift;

    // Shift the floor.
    for (; int_shift > 0; --int_shift) {
        // XXX For better performance, move this copy out of
        // the loop.
        for (int col = 0; col < COLS - 1; col++)
            tiles[col] = tiles[col + 1];
        static uniform_real_distribution<float> distribution;
        if (distribution(generator) <= hole_prob)
            tiles[COLS - 1] = ' ';
        else
            tiles[COLS - 1] = floor_tile();
    }
    return false;
}

bool Floor::on_space(void) {
    return tiles[1] == ' ';
}
