#include "s21_tetris_frontend.h"

void s21_render_final_score(settings_t *settings) {
  mvwprintw(settings->tetris, 31, 24, "GAME OVER");
  mvwprintw(settings->tetris, 32, 20, "Your final score");
  mvwprintw(settings->tetris, 34, 16, "+--------------------+");
  mvwprintw(settings->tetris, 35, 16, "|(%-10s: %.6d)|", settings->name,
            settings->score);
  mvwprintw(settings->tetris, 36, 16, "+--------------------+");
  mvwprintw(settings->tetris, 38, 8, "Press R to restart or Q to finish the game");
}