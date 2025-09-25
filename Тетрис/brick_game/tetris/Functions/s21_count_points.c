#include "s21_tetris_backend.h"

void s21_count_points(int full_rows) {
  int score = 0;
  switch (full_rows) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
  }

  current_game_state.score += score;
  s21_calculate_level();
  s21_calculate_speed();
  s21_update_leaderboard();
}