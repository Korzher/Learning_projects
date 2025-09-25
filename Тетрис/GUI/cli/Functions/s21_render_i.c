#include "s21_tetris_frontend.h"

void s21_render_i(settings_t *settings, int y, int x) {
  int color_map[7][7] = {{W, W, W, W, W, W, W}, {A, A, A, W, A, A, A},
                         {A, A, A, W, A, A, A}, {A, A, A, W, A, A, A},
                         {A, A, A, C, A, A, A}, {A, A, A, C, A, A, A},
                         {W, W, C, C, W, W, W}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(settings->tetris, COLOR_PAIR(color));
      mvwaddch(settings->tetris, y + i, x + j, '#');
      wattroff(settings->tetris, COLOR_PAIR(color));
    }
  }
}