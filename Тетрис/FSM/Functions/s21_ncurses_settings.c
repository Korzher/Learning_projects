#include "s21_FSM.h"

void s21_ncurses_settings() {
  initscr();
  cbreak();
  noecho();
  clear();
  refresh();
  nodelay(stdscr, TRUE);
  start_color();
  curs_set(0);
  srand(time(NULL));
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_BLACK);
}