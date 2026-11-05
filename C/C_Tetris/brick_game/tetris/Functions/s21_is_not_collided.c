#include "s21_tetris_backend.h"

int s21_is_not_collided(int test_x, int test_y) {
  int not_collided = SUCCESS;
  for (int i = 0; i < BLOCKS && not_collided == SUCCESS; i++) {
    int new_x = test_x + current_game_state.current_piece.blocks[i].x;
    int new_y = test_y + current_game_state.current_piece.blocks[i].y;

    if (new_x < 0 || new_x >= FIELD_WIDTH) {
      not_collided = ERROR;
    }

    if (new_y >= FIELD_HEIGHT || new_y < 1) {
      not_collided = ERROR;
    }

    if (new_y >= 0 && current_game_state.field[new_y][new_x] != 0) {
      not_collided = ERROR;
    }
  }

  return not_collided;
}