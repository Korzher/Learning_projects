#ifndef S21_FSM_H
#define S21_FSM_H

#include "../s21_defines.h"
#include "../s21_objects.h"
#include "../GUI/cli/s21_tetris_frontend.h"
#include "../brick_game/tetris/s21_tetris_backend.h"
#include <time.h>
#include <locale.h>

void s21_ncurses_settings(void);
void s21_game_loop();
void s21_state_act(UserAction_t action, GameState *state, Windows_t *windows);
void s21_do_game_start(UserAction_t action, GameState *state);
void s21_do_name_insert(GameState *state);
void s21_do_spawn(GameState *state);
void s21_do_moving(UserAction_t action, GameState *state);
void s21_do_pause(GameState *state);
void s21_do_attach(GameState *state);
void s21_do_game_over(UserAction_t action, GameState *state);
void s21_create_game_state(Windows_t *windows);
void s21_delete_game_state(Windows_t *windows);

#endif
