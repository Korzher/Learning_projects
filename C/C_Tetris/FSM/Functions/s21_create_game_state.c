#include "s21_FSM.h"

void s21_create_game_state(GameState_t *current_state, GameInfo_t *game_info) {
  game_info->level = 1;
  game_info->speed = 30;
  game_info->score = 0;
  current_state->state = GAME_START;
  current_state->frames = 0;
  current_state->next_piece.type = -1;
  current_state->tetris = newwin(42, 60, 0, 0);
  current_state->game_field = newwin(FIELD_HEIGHT, FIELD_WIDTH, 7, 13);
  current_state->next_piece_field = newwin(5, 7, 7, 31);
  current_state->leaderboard_field = newwin(9, 20, 20, 31);
  box(current_state->tetris, ACS_VLINE, ACS_HLINE);
  wrefresh(current_state->tetris);
}