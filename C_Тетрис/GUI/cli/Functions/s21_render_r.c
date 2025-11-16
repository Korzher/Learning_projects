#include "s21_tetris_frontend.h"

void s21_render_r(settings_t *settings, int y, int x) {
  int color_map[7][7] = {{W, W, W, W, W, W, A}, {W, A, A, A, A, A, W},
                         {U, A, A, A, A, A, W}, {U, U, W, W, W, W, A},
                         {U, A, A, W, A, A, A}, {W, A, A, A, W, A, A},
                         {W, A, A, A, A, W, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(settings->tetris, COLOR_PAIR(color));
      mvwaddch(settings->tetris, y + i, x + j, '#');
      wattroff(settings->tetris, COLOR_PAIR(color));
    }
  }
}