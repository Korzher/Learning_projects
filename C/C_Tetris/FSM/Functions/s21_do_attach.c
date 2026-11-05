#include "s21_FSM.h"

void s21_do_attach(GameState *state) {
  s21_attach();
  *state = SPAWN;
}