#include "s21_tetris_backend.h"

void s21_destroy_rows() {
  int full_rows = 0;

  for (int y = FIELD_HEIGHT - 2; y >= 1; y--) {
    int row_full = 1;

    for (int x = 1; x < FIELD_WIDTH - 1; x++) {
      if (current_game_state.field[y][x] == 0) {
        row_full = 0;
        break;
      }
    }

    if (row_full) {
      full_rows++;
      for (int ny = y; ny > 0; ny--) {
        for (int x = 1; x < FIELD_WIDTH - 1; x++) {
          current_game_state.field[ny][x] = current_game_state.field[ny - 1][x];
        }
      }
      for (int x = 1; x < FIELD_WIDTH - 1; x++) {
        current_game_state.field[1][x] = 0;
      }

      y++;
    }
  }

  if (full_rows > 0) {
    s21_count_points(full_rows);
  }
}