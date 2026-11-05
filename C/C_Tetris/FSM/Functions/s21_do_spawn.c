#include "s21_FSM.h"

void s21_do_spawn(GameState *state) {
  if (current_game_state.next_piece.type == -1) {
    s21_spawn_new_piece();
  }
  if (s21_spawn_new_piece()) {
    *state = MOVING;
  } else {
    *state = GAME_OVER;
  }
}