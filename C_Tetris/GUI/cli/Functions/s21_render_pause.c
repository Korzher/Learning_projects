#include "s21_tetris_frontend.h"

void s21_render_pause(settings_t *settings) {
  werase(settings->tetris);
  werase(settings->game_field);
  werase(settings->leaderboard_field);
  werase(settings->next_piece_field);
  box(settings->tetris, ACS_VLINE, ACS_HLINE);
  mvwprintw(settings->tetris, 4, 26, "TETRIS");

  mvwprintw(settings->tetris, 15, 1,
            "__________________________________________________________");
  mvwprintw(settings->tetris, 18, 26, "PAUSE");
  mvwprintw(settings->tetris, 21, 1,
            "__________________________________________________________");

  wrefresh(settings->tetris);
}