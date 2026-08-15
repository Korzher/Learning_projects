#include "s21_tetris_backend.h"

void s21_update_leaderboard() {
  int pos = current_game_state.leaderboard_pos;
  current_game_state.leaderboard[pos].score = current_game_state.score;

  while (pos > 0 && current_game_state.leaderboard[pos].score >
                        current_game_state.leaderboard[pos - 1].score) {
    HighScore_t temp = current_game_state.leaderboard[pos];
    current_game_state.leaderboard[pos] =
        current_game_state.leaderboard[pos - 1];
    current_game_state.leaderboard[pos - 1] = temp;
    pos--;
  }
  current_game_state.leaderboard_pos = pos;
}