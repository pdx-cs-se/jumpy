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
    int y = 1;
    char shape[3] = { '\\', 'M', 'O' };

public:
    // XXX Jumpy should be drawn last so that the cursor
    // ends up over their body.
    void draw(void) {
        for (int i = 0; i < 3; i++) 
            mvaddch(LINES - y - i - 1, 2, shape[i]);
        move(LINES - y - 2, 2);
    }
};

int main() {
  // Set up ncurses.
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);

  // Initialize game state.
  auto floor = Floor();
  auto jumpy = Jumpy();

  // Game loop.
  while (true) {
      // Update the current game state.
      floor.update();

      // Show the current game state.
      floor.draw();
      jumpy.draw();
      refresh();

      // Wait a bit.
      auto delay_time = chrono::milliseconds(1000 / FRAME_RATE);
      this_thread::sleep_for(delay_time);
  }

  // Clean up.
  endwin();
  return 0;
}
