#include "s21_tetris_backend.h"

void s21_calculate_speed() {
  current_game_state.speed = 32 - (current_game_state.level * 2);
}