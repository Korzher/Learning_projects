#include "s21_FSM.h"

void s21_do_name_insert(GameState *state) {
  s21_init_game();
  s21_load_leaderboard();
  *state = SPAWN;
}