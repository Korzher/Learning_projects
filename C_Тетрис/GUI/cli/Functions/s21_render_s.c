#include "s21_tetris_frontend.h"

void s21_render_s(settings_t *settings, int y, int x) {
  int color_map[7][7] = {{A, R, R, R, R, W, A}, {W, A, A, A, A, A, A},
                         {W, A, A, A, A, A, A}, {A, W, R, R, R, R, A},
                         {A, A, A, A, A, A, W}, {A, A, A, A, A, A, W},
                         {A, R, R, R, R, W, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(settings->tetris, COLOR_PAIR(color));
      mvwaddch(settings->tetris, y + i, x + j, '#');
      wattroff(settings->tetris, COLOR_PAIR(color));
    }
  }
}