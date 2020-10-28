// Jumpy — Side-scrolling runner / platformer
// CS 300 Fall 2020 class
// In-class Game Jam 2020: Theme "cursed"

#include <chrono>
#include <cstring>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <ncurses.h>

using namespace std;

// Jump velocity in chars per frame.
const float JUMP_VEL = 1.5;

// Jump deceleration in chars per frame per frame.
const float JUMP_DECEL = 0.2;

// Draw the floor.
class Floor {
    vector<char> tiles;

    static char floor_tile(void) {
        static string terrain = "#*O@";
        static default_random_engine generator;
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

    void update(void) {
        for (int col = 0; col < COLS - 1; col++)
            tiles[col] = tiles[col + 1];
        tiles[COLS - 1] = floor_tile();
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

    void update(void) {
        pos_y += vel_y;
        if (pos_y <= 1.0) {
            pos_y = 1.0;
            vel_y = 0.0;
            return;
        }
        vel_y -= JUMP_DECEL;
    }

    void jump(void) {
        // No double jumps.
        // XXX Should let clipping take care of this.
        if (pos_y > 1.0)
            return;
        
        vel_y = JUMP_VEL;
    }
};

int main(int argc, char* argv[]) {
  int frameRate = 30;
  if (argc > 1 && strcmp(argv[1], "Dark Souls"))
    frameRate = 60;
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
      floor.update();
      jumpy.update();

      // Show the current game state.
      erase();
      floor.draw();
      jumpy.draw();
      refresh();

      // Wait a bit.
      auto delay_time = chrono::milliseconds(1000 / frameRate);
      this_thread::sleep_for(delay_time);
  }

  // Clean up.
  endwin();
  return 0;
}
