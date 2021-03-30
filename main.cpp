// Main File Assignment 3: Game of Life
// Implemented by Tijmen van Etten, 11781289
// OS: macOS Big Sur, 11.2.3
// Compiler: Apple clang version 11.0.0 (clang-1100.0.33.12)
// Target: x86_64-apple-darwin19.6.0#include <iostream>
#include "classes.h"

int main() {
  // Initialize Game of Life with a menu
  Menu game_menu;
  // Keep menu open
  while (true) {
    // Check for menu selection
    game_menu.check_input();
  }
  return 0;
}