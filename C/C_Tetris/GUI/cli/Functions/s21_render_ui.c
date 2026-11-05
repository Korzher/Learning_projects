#include "s21_tetris_frontend.h"

void s21_render_ui(settings_t *settings) {
  mvwprintw(settings->tetris, 6, 31, "NEXT PIECE:");
  mvwprintw(settings->tetris, 14, 31, "Name:");
  mvwprintw(settings->tetris, 15, 31, "%s", settings->name);
  mvwprintw(settings->tetris, 17, 31, "Score:");
  mvwprintw(settings->tetris, 18, 31, "%d", settings->score);
  mvwprintw(settings->tetris, 19, 35, "Leaderboard:");
  mvwprintw(settings->tetris, 29, 15, "Level: %d", settings->level);
  mvwprintw(settings->tetris, 31, 13, "Controls");
  mvwprintw(settings->tetris, 32, 13, "A - Shift left");
  mvwprintw(settings->tetris, 33, 13, "D - Shift right");
  mvwprintw(settings->tetris, 34, 13, "S - Drop tetramino");
  mvwprintw(settings->tetris, 35, 13, "W - Rotate tetramino");
  mvwprintw(settings->tetris, 36, 13, "P - Pause");
  mvwprintw(settings->tetris, 37, 13, "Q - Quit");
}