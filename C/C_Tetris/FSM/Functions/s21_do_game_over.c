#include "s21_FSM.h"

void s21_do_game_over(UserAction_t action, GameState *state) {
  s21_save_leaderboard();
  s21_free_game_info();
  if (action == Start) {
    s21_init_game_info();
    *state = NAME_INSERT;
  } else if (action == Terminate) {
    *state = END_GAME;
  }
}