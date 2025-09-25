#include "s21_tetris_frontend.h"

void s21_render_name(settings_t *settings) {
  werase(settings->tetris);
  box(settings->tetris, ACS_VLINE, ACS_HLINE);

  s21_render_logo(settings);
  s21_render_name_placeholder(settings);
  wrefresh(settings->tetris);
  s21_render_name_register(settings);
}