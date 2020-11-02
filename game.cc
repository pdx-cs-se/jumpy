// Jumpy — Side-scrolling runner / platformer
// CS 300 Fall 2020 class
// In-class Game Jam 2020: Theme "cursed"

#include <chrono>
#include <cstdint>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <ncurses.h>

#include "game.h"
#include "gamestate.h"

default_random_engine generator;

int main() {
  // Set up ncurses.
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);

  // Initialize game state.
  GameState state;

  // Game loop.
  while (true) {
      // Process keypresses.
      switch (getch()) {
      case ' ':
          state.jumpy.jump();
          break;
      }

      // Update the current game state.
      if (state.update())
          break;

      // Show the current game state.
      erase();
      state.draw();
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
