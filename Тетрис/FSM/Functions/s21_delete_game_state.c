#include "s21_FSM.h"

void s21_delete_game_state(settings_t* settings) {
  delwin(settings->tetris);
  delwin(settings->game_field);
  delwin(settings->next_piece_field);
  delwin(settings->leaderboard_field);
}