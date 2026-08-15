#include "s21_FSM.h"

void s21_game_loop() {
  Windows_t windows = {0};
  s21_create_game_state(&windows);
  int break_flag = TRUE;
  GameState state = GAME_START;
  int signal = 0;
  while (break_flag) {
    if (state == END_GAME) break_flag = FALSE;

    if (state == MOVING || state == GAME_START || state == GAME_OVER)
      signal = getch();

    s21_state_act(s21_get_user_input(signal), &state, &windows);
    napms(16);
  }
  s21_delete_game_state(&windows);
}

void s21_state_act(UserAction_t action, GameState *state, Windows_t *windows) {
  switch (*state) {
    case GAME_START:
      s21_render_start(windows);
      s21_init_game_info();
      s21_do_game_start(action, state);
      break;
    case NAME_INSERT:
      s21_render_name(windows);
      s21_do_name_insert(state);
      break;
    case SPAWN:
      s21_do_spawn(state);
      s21_render_field(windows);
      break;
    case MOVING:
      s21_do_moving(action, state);
      s21_render_field(windows);
      break;
    case SHIFT:
      s21_render_field(windows);
      *state = MOVING;
      break;
    case PAUSE:
      s21_render_pause(windows);
      s21_do_pause(state);
      break;
    case ATTACH:
      s21_render_field(windows);
      s21_do_attach(state);
      break;
    case GAME_OVER:
      s21_render_end_game(windows);
      s21_do_game_over(action, state);
      break;
    case END_GAME:
      break;
    default:
      break;
  }
}
