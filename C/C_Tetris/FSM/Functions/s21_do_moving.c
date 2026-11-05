#include "s21_FSM.h"

void s21_do_moving(UserAction_t action, GameState *state) {
  s21_user_input(action);
  if (action == Left || action == Right || action == Action) {
    *state = SHIFT;
  } else if (action == Down) {
    *state = ATTACH;
  } else if (action == Pause) {
    *state = PAUSE;
  } else if (action == Terminate) {
    *state = GAME_OVER;
  }

  if (*state != PAUSE) {
    current_game_state.frames++;
    if (current_game_state.frames == current_game_state.speed ||
        current_game_state.frames > current_game_state.speed) {
      *state = s21_move();
      current_game_state.frames = 0;
    }
  }
}