#include "s21_tetris_backend.h"

void s21_init_game() {
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      current_game_state.field[y][x] = 0;
      if (x == 0 || x == FIELD_WIDTH - 1 || y == FIELD_HEIGHT - 1) {
        current_game_state.field[y][x] = -1;
      }
    }
  }
}