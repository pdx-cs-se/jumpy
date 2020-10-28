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
  // XXX Game code goes here.
  endwin();
  return 0;
}
