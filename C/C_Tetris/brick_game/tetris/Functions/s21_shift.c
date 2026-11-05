#include "s21_tetris_backend.h"

void s21_shift(int step) {
  int new_x = current_game_state.current_piece.x + step;

  if (s21_is_not_collided(new_x, current_game_state.current_piece.y) ==
      SUCCESS) {
    current_game_state.current_piece.x = new_x;
  }
}