#include "s21_FSM.h"

void s21_do_pause(UserAction_t action, GameState *state) {
  if (action == Pause && !current_game_state.pause) {
    current_game_state.pause = !current_game_state.pause;
    *state = PAUSE;
    while (s21_get_user_input(getch()) != Pause) {
    };
  } else if (action == Pause && current_game_state.pause) {
    current_game_state.pause = !current_game_state.pause;
    *state = MOVING;
  } else if (action == Terminate) {
    *state = GAME_OVER;
  }
}