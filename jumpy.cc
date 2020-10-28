// Jumpy — Side-scrolling runner / platformer
// CS 300 Fall 2020 class
// In-class Game Jam 2020: Theme "cursed"

#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <ncurses.h>

using namespace std;

// Frame rate in frames per second.
const int FRAME_RATE = 30;

// Jump velocity in chars per frame.
const float JUMP_VEL = 1.5;

// Jump deceleration in chars per frame per frame.
const float JUMP_DECEL = 0.2;

// PRNG.
default_random_engine generator;

// Draw the floor.
class Floor {
    vector<char> tiles;
    float hole_prob = 0.01;

    static char floor_tile(void) {
        static string terrain = "#*O@";
        static uniform_int_distribution<int>
            distribution(0, terrain.length() - 1);
        int terrain_index = distribution(generator);
        return terrain[terrain_index];
    }

public:
    Floor() {
        for (int i = 0; i < COLS; i++)
            tiles.push_back(floor_tile());
    }

    // Draw the current floor.
    void draw(void) {
        for (int col = 0; col < COLS; col++)
            mvaddch(LINES - 1, col, tiles[col]);
    }

    // Returns true on game over.
    bool update(void) {
        for (int col = 0; col < COLS - 1; col++)
            tiles[col] = tiles[col + 1];
        static uniform_real_distribution<float> distribution;
        if (distribution(generator) <= hole_prob)
            tiles[COLS - 1] = ' ';
        else
            tiles[COLS - 1] = floor_tile();
        return false;
    }

    bool on_space(void) {
        return tiles[1] == ' ';
    }
};

class Jumpy {
    // Jumpy's current y velocity.
    float vel_y = 0.0;
    // Jumpy's current y position.
    float pos_y = 1.0;
    char shape[3] = { '\\', 'M', 'O' };

public:
    // XXX Jumpy should be drawn last so that the cursor
    // ends up over their body.
    void draw(void) {
        int y = floor(pos_y + 0.5);
        for (int i = 0; i < 3; i++) 
            mvaddch(LINES - y - i - 1, 2, shape[i]);
        move(LINES - y - 2, 2);
    }

    // Returns true on game over.
    // XXX Needs more principled state sharing.
    bool update(Floor &floor) {
        pos_y += vel_y;
        if (pos_y <= 1.0) {
            if (floor.on_space()) {
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

    void jump(void) {
        // No double jumps.
        // XXX Should let clipping take care of this.
        if (pos_y > 1.0)
            return;
        
        vel_y = JUMP_VEL;
    }
};

int main() {
  // Set up ncurses.
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);

  // Initialize game state.
  auto floor = Floor();
  auto jumpy = Jumpy();

  // Game loop.
  while (true) {
      // Process keypresses.
      switch (getch()) {
      case ' ':
          jumpy.jump();
          break;
      }

      // Update the current game state.
      bool floor_fail = floor.update();
      bool jumpy_fail = jumpy.update(floor);
      if (floor_fail || jumpy_fail)
          break;

      // Show the current game state.
      erase();
      floor.draw();
      jumpy.draw();
      refresh();

      // Wait a bit.
      auto delay_time = chrono::milliseconds(1000 / FRAME_RATE);
      this_thread::sleep_for(delay_time);
  }

  // Clean up.
  refresh();
  auto delay_time = chrono::seconds(5);
  this_thread::sleep_for(delay_time);
  endwin();
  return 0;
}
