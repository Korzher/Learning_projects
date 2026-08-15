#include "s21_tetris_frontend.h"

void s21_render_field(settings_t *settings) {
  werase(settings->tetris);
  mvwprintw(settings->tetris, 4, 26, "TETRIS");
  box(settings->tetris, ACS_VLINE, ACS_HLINE);
  box(settings->game_field, ACS_VLINE, ACS_HLINE);
  box(settings->leaderboard_field, ACS_VLINE, ACS_HLINE);
  box(settings->next_piece_field, ACS_VLINE, ACS_HLINE);

  s21_render_ui(settings);
  s21_render_next_piece(settings);
  s21_render_game_field(settings);
  s21_render_leaderboard(settings);

  wrefresh(settings->tetris);
  wrefresh(settings->game_field);
  wrefresh(settings->leaderboard_field);
  wrefresh(settings->next_piece_field);
}