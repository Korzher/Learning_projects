#include "s21_tetris_frontend.h"

void s21_render_e(settings_t *settings, int y, int x) {
  int color_map[7][7] = {{W, O, O, O, W, W, W}, {W, O, A, A, A, A, A},
                         {W, W, A, A, A, A, A}, {W, W, W, W, W, W, W},
                         {W, W, A, A, A, A, A}, {M, M, A, A, A, A, A},
                         {W, M, M, W, W, W, W}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(settings->tetris, COLOR_PAIR(color));
      mvwaddch(settings->tetris, y + i, x + j, '#');
      wattroff(settings->tetris, COLOR_PAIR(color));
    }
  }
}