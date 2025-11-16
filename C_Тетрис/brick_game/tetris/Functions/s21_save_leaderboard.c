#include "s21_tetris_backend.h"

void s21_save_leaderboard() {
  FILE *leaderboard = fopen(FILENAME, "w");
  int lines = current_game_state.leaderboard_size > MAX_LB_LINES
                  ? MAX_LB_LINES
                  : current_game_state.leaderboard_size;
  for (int i = 0; i < lines; i++) {
    fprintf(leaderboard, "%s %.6d\n", current_game_state.leaderboard[i].name,
            current_game_state.leaderboard[i].score);
  }
  fclose(leaderboard);
}
