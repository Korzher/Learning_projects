#include "s21_FSM.h"

void s21_do_game_start(UserAction_t action, GameState *state) {
  if (action == Start) {
    s21_user_input(action);
    *state = NAME_INSERT;
  }
}