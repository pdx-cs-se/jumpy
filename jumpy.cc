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

int main() {
  // Set up ncurses.
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);

  // Initialize game state.
  auto floor = Floor();

  // Game loop.
  while (true) {
      // Update the current game state.
      floor.update();

      // Show the current game state.
      floor.draw();
      refresh();

      // Wait a bit.
      auto delay_time = chrono::milliseconds(30);
      this_thread::sleep_for(delay_time);
  }

  // Clean up.
  endwin();
  return 0;
}
