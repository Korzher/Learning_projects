#include "s21_tetris_frontend.h"

void s21_render_t(settings_t *settings, int y, int x) {
  int color_map[7][7] = {{G, G, W, W, W, W, W}, {G, G, W, W, W, W, W},
                         {A, A, W, W, W, A, A}, {A, A, W, W, W, A, A},
                         {A, A, W, W, W, A, A}, {A, A, W, G, G, A, A},
                         {A, A, W, G, G, A, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(settings->tetris, COLOR_PAIR(color));
      mvwaddch(settings->tetris, y + i, x + j, '#');
      wattroff(settings->tetris, COLOR_PAIR(color));
    }
  }
}
