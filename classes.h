// Header File Assignment 3: Game of Life
// Implemented by Tijmen van Etten, 11781289
// OS: macOS Big Sur, 11.2.3
// Compiler: Apple clang version 11.0.0 (clang-1100.0.33.12)
// Target: x86_64-apple-darwin19.6.0
class PRNG {
  /*
  Pseudo-Random-Number-Generator class
  */
public:
  PRNG();
  int seed;
  double draw();

private:
  static const int A = 214013;
  static const int C = 2531011;
  static const long M = 2147483648;
};

class World {
  /*
  World class: saves board and manages PRNG
  */
public:
  World();
  char DEAD_CELL_REPR, LIFE_CELL_REPR;
  void show(int x, int y), update(), clean(), randomize(), open_file(),
      set_seed(), set_survival_p();

private:
  PRNG prng;
  // Create 200x200 board with 1x1 border
  int board[202][202];
  int boardBorderSum[202][202];
  double p_survival;
};

class Menu {
  /*
  Menu class: manages user commands and world manipulation.
  */
public:
  Menu();
  void check_input();

private:
  World world;
  int view_x, view_y, x_step_size, y_step_size;
  void run_simulation(), move_viewpoint(), set_parameters();
};