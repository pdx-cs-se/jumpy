// Jumpy — Side-scrolling runner / platformer
// CS 300 Fall 2020 class
// In-class Game Jam 2020: Theme "cursed"

#include <chrono>
#include <thread>

#include <ncurses.h>

using namespace std;

int main() {
  // Set up ncurses.
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);

  // Draw the floor.
  for (int col = 0; col < COLS; col++)
      mvaddch(LINES - 1, col, '#');
  refresh();

  // Wait a bit.
  auto delay_time = chrono::seconds(3);
  this_thread::sleep_for(delay_time);

  // Clean up.
  endwin();
  return 0;
}
