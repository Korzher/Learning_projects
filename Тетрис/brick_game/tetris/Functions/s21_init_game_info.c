#include "s21_tetris_backend.h"

void s21_init_game_info() {
  s21_free_game_info();
  current_game_state.field = malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    current_game_state.field[i] = malloc(FIELD_WIDTH * sizeof(int));
    memset(current_game_state.field[i], 0, FIELD_WIDTH * sizeof(int));
  }
  current_game_state.score = 0;
  current_game_state.level = 1;
  current_game_state.speed = 38;
  current_game_state.pause = 0;
  current_game_state.frames = 0;
  current_game_state.next_piece.type = -1;
};