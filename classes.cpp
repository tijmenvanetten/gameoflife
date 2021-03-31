// Class File Assignment 3: Game of Life
// Implemented by Tijmen van Etten, 11781289
// OS: macOS Big Sur, 11.2.3
// Compiler: Apple clang version 11.0.0 (clang-1100.0.33.12)
// Target: x86_64-apple-darwin19.6.0
#include "classes.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

PRNG::PRNG() {
  // Set default seed from time
  seed = time(NULL);
}

void World::set_seed() {
  cout << "Enter seed: ";
  cin >> prng.seed;
}

double PRNG::draw() {
  // Linear Congruent Generator Implementation
  seed = ((A * seed + C) % M);
  // Scale from 0 to 1
  return abs((double)seed / M);
}

World::World() {
  // Construct world with clean board
  clean();
  DEAD_CELL_REPR = '.';
  LIFE_CELL_REPR = '#';
  p_survival = 0.5;
}

void World::open_file() {
  cout << "Specify filename: ";
  // Open filestream from file name specified by user
  char file_name[50];
  cin >> file_name;
  ifstream filestream(file_name);
  char cell;
  for (int row = 1; row < 201; row++) {
    for (int col = 1; col < 201; col++) {
      filestream.get(cell);
      if (cell == '\n') {
        break;
      }
      // Set life cells to 1 on board
      else if (cell == LIFE_CELL_REPR) {
        board[row][col] = 1;
      }
      // Set dead cells to 0 on board
      else {
        board[row][col] = 0;
      }
    }
  }
}

void World::show(int x, int y) {
  // Output 30x90 relative to top-left x,y coordinates
  cout << x << ',' << y << " (x,y)\n";
  for (int row = x; row < (x + 30); row++) {
    for (int col = y; col < (y + 90); col++) {
      // Output '#' if location is out of grid
      if ((row < 0) || (row >= 200) || (col < 0) || (col >= 200)) {
        cout << ' ';
      } else {
        // Print dead or life cell based on entry
        if (board[row][col]) {
          cout << LIFE_CELL_REPR;
        } else {
          cout << DEAD_CELL_REPR;
        }
      }
    }
    cout << '\n';
  }
  cout << '\n';
}

void World::update() {
  // Iterate over board
  for (int row = 1; row < 201; row++) {
    for (int col = 1; col < 201; col++) {
      // Count alive adjacent cells
      boardBorderSum[row][col] = board[row + 1][col - 1] + board[row + 1][col] +
                                 board[row + 1][col + 1] + board[row][col - 1] +
                                 board[row][col + 1] + board[row - 1][col - 1] +
                                 board[row - 1][col] + board[row - 1][col + 1];
    }
  }
  // Set value for each cell based on the sum of alive neighbors
  for (int row = 1; row < 201; row++) {
    for (int col = 1; col < 201; col++) {
      // Case for life cells
      if (board[row][col] == 1) {
        // Kill life cell based on condition
        if ((boardBorderSum[row][col] < 2) || (boardBorderSum[row][col] > 3)) {
          board[row][col] = 0;
        }
      }
      // Revive dead cell with 3 alive neighbors
      else if (boardBorderSum[row][col] == 3) {
        board[row][col] = 1;
      }
    }
  }
}

void World::clean() {
  // Set each cell on board to 0
  for (int row = 0; row < 202; row++) {
    for (int col = 0; col < 202; col++) {
      board[row][col] = 0;
    }
  }
}

void World::randomize() {
  for (int row = 1; row < 201; row++) {
    for (int col = 1; col < 201; col++) {
      // Set life cell based on random number
      // and survival probability
      if (prng.draw() < p_survival) {
        board[row][col] = 1;
      } else
        board[row][col] = 0;
    }
  }
}

void World::set_survival_p() {
  cout << "Enter survival probability: ";
  cin >> p_survival;
}

// Menu Constructor
Menu::Menu() {
  view_x = 1, view_y = 1;
  x_step_size = 1, y_step_size = 1;
}

void Menu::check_input() {
  cout << "Enter command:\n"
       << "1: Show Board        "
       << "2: Clean Board       "
       << "3: Randomize Board   " << endl
       << "4: Update Board      "
       << "5: Go 100 times      "
       << "6: Move viewpoint    " << endl
       << "7: Set Parameters    "
       << "8: Open File         "
       << "0: Exit Program      " << endl;
  int command;
  cin >> command;
  // While the input entered is not an integer, prompt the user to enter an
  // integer.
  while (!cin) {
    cout << "Enter command: \n";
    cin.clear();
    cin.ignore();
    cin >> command;
  }
  switch (command) {
  case 0:
    exit(0);
    break;
  case 1:
    world.show(view_x, view_y);
    break;
  case 2:
    world.clean();
    world.show(view_x, view_y);
    break;
  case 3:
    world.randomize();
    world.show(view_x, view_y);
    break;
  case 4:
    world.update();
    world.show(view_x, view_y);
    break;
  case 5:
    run_simulation();
    break;
  case 6:
    move_viewpoint();
    break;
  case 7:
    set_parameters();
    break;
  case 8:
    world.open_file();
    break;
  default:
    break;
  };
}

void Menu::run_simulation() {
  // Update board 100 steps and show each step
  for (int i = 0; i < 100; i++) {
    world.update();
    world.show(view_x, view_y);
    usleep(50000);
  }
}

void Menu::move_viewpoint() {
  // MAKE SURE CANNOT GO OFF GRID
  int direction;
  bool check = true;
  while (check) {
    world.show(view_x, view_y);
    cout << "Enter command: \n"
         << "  1: Left\n"
         << "  2: Right\n"
         << "  3: Up\n"
         << "  4: Down\n"
         << "  5: Save\n";
    cin >> direction;
    // While the input entered is not an integer, prompt the user to enter an
    // integer.
    while (!cin) {
      cout << "Enter direction: \n";
      cin.clear();
      cin.ignore();
      cin >> direction;
    }
    switch (direction) {
    case 1:
      view_y -= y_step_size;
      break;
    case 2:
      view_y += y_step_size;
      break;
    case 3:
      view_x -= y_step_size;
      break;
    case 4:
      view_x += y_step_size;
      break;
    case 5:
      check = false;
    default:
      break;
    };
    // Make sure grid is always in sight
    if (view_x < -15)
      view_x = -15;
    if (view_x > 15)
      view_x = 15;
    if (view_y < -30)
      view_y = -30;
    if (view_y > 30)
      view_y = 30;
  }
}

void Menu::set_parameters() {
  cout << "Enter command:\n"
       << "  1: Set X step-size               "
       << "  2: Set Y step-size               "
       << "  3: Set surival probability       " << endl
       << "  4: Set Life cell representation  "
       << "  5: Set Dead cell representation  "
       << "  6: Set Seed                      " << endl
       << "  0: Save                          " << endl;
  int command;
  cin >> command;
  // While the input entered is not an integer, prompt the user to enter an
  // integer.
  while (!cin) {
    cout << "Enter command: \n";
    cin.clear();
    cin.ignore();
    cin >> command;
  }
  switch (command) {
  case 1:
    cout << "Enter X step-size: ";
    cin >> x_step_size;
    break;
  case 2:
    cout << "Enter Y step-size: ";
    cin >> y_step_size;
    break;
  case 3:
    world.set_survival_p();
    break;
  case 4:
    cout << "Provide character representation of a life cell: ";
    cin >> world.LIFE_CELL_REPR;
    break;
  case 5:
    cout << "Provide character representation of a dead cell: ";
    cin >> world.DEAD_CELL_REPR;
    break;
  case 6:
    world.set_seed();
  default:
    break;
  };
}
