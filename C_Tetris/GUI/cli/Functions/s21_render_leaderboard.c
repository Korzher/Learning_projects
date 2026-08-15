#include "s21_tetris_frontend.h"

void s21_render_leaderboard(settings_t *settings) {
  int lines = settings->leaderboard_size > MAX_LB_LINES ? MAX_LB_LINES : settings->leaderboard_size;
  for (int i = 0; i < lines; i++) {
    mvwprintw(settings->leaderboard_field, i + 1, 1, "%-10s: %.6d", settings->leaderboard[i].name, settings->leaderboard[i].score);
  }
}