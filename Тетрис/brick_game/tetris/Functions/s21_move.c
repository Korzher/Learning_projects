#include "s21_tetris_backend.h"

int s21_move() {
  int state = MOVING;
  int new_y = current_game_state.current_piece.y + 1;

  if (s21_is_not_collided(current_game_state.current_piece.x, new_y) ==
      SUCCESS) {
    current_game_state.current_piece.y = new_y;
  } else {
    state = ATTACH;
  }

  return state;
}