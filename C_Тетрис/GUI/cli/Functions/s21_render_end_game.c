#include "s21_tetris_frontend.h"

void s21_render_end_game(settings_t *settings) {
  werase(settings->tetris);
  box(settings->tetris, ACS_VLINE, ACS_HLINE);

  s21_render_logo(settings);
  s21_render_final_score(settings);
  wrefresh(settings->tetris);
}