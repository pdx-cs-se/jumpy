#include <ncurses.h>

#include "gamestate.h"
#include "jumpy.h"

using namespace std;

// XXX Jumpy should be drawn last so that the cursor
// ends up over their body.
void Jumpy::draw(void) {
    int y = floor(pos_y + 0.5);
    for (int i = 0; i < 3; i++) 
        mvaddch(LINES - y - i - 1, 2, shape[i]);
    move(LINES - y - 2, 2);
}

// Returns true on game over.
bool Jumpy::update(GameState &state) {
    pos_y += vel_y;
    if (pos_y <= 1.0) {
        if (state.floor.on_space()) {
            pos_y = 0.0;
            return true;
        }
        pos_y = 1.0;
        vel_y = 0.0;
        return false;
    }
    vel_y -= JUMP_DECEL;
    return false;
}

// Start a fresh jump.
void Jumpy::jump(void) {
    // No double jumps.
    // XXX Should let clipping take care of this.
    if (pos_y > 1.0)
        return;

    vel_y = JUMP_VEL;
}
