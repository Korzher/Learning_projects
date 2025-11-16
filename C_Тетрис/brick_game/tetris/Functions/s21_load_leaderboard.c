#include "s21_tetris_backend.h"

void s21_load_leaderboard() {
  FILE *scores_file = fopen(FILENAME, "r");
  if (scores_file == NULL) {
    printf("Error opening leaderboard file.\n");
    return;
  }
  int lines = 0;
  while (lines < MAX_LB_LINES &&
         fscanf(scores_file, "%s %d",
                current_game_state.leaderboard[lines].name,
                &current_game_state.leaderboard[lines].score) == 2) {
    lines++;
  }
  fclose(scores_file);
  strncpy(current_game_state.leaderboard[lines].name, current_game_state.name,
          11);
  current_game_state.leaderboard[lines].score = current_game_state.score;
  current_game_state.leaderboard_pos = lines;
  lines++;
  current_game_state.leaderboard_size = lines;
}