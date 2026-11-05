#include "s21_tetris_frontend.h"

void s21_render_name_placeholder(settings_t *settings) {
  mvwprintw(settings->tetris, 32, 19, "ENTER YOUR NAME");
  mvwprintw(settings->tetris, 34, 20, "+-----------+");
  mvwprintw(settings->tetris, 35, 20, "|           |");
  mvwprintw(settings->tetris, 36, 20, "+-----------+");
  mvwprintw(settings->tetris, 38, 14, "Press ENTER to start the game");
}