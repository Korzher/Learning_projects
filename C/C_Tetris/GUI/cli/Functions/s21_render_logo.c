#include "s21_tetris_frontend.h"

void s21_render_logo(settings_t *settings) {
  s21_render_t(settings, 10, 4);
  s21_render_e(settings, 10, 13);
  s21_render_t(settings, 10, 22);
  s21_render_r(settings, 10, 31);
  s21_render_i(settings, 10, 40);
  s21_render_s(settings, 10, 49);
}