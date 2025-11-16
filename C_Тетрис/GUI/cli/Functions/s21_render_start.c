#include "s21_tetris_frontend.h"

void s21_render_start(settings_t *settings) {
  s21_render_logo(settings);
  mvwprintw(settings->tetris, 35, 15, "Press R to start the game");
  wrefresh(settings->tetris);
}