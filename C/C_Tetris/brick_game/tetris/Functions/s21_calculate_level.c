#include "s21_tetris_backend.h"

void s21_calculate_level() {
  current_game_state.level = current_game_state.score / 600 + 1;
  if (current_game_state.level > 10) {
    current_game_state.level = 10;
  }
}