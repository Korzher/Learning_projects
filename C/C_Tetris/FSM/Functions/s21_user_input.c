#include "s21_FSM.h"

void s21_user_input(UserAction_t action) {
  switch (action) {
    case Start:
      break;
    case Pause:
      break;
    case Terminate:
      break;
    case Left:
      s21_shift(-1);
      break;
    case Right:
      s21_shift(1);
      break;
    case Up:
      break;
    case Down:
      while (s21_move() != ATTACH) {
      };
      break;
    case Action:
      s21_rotate();
      break;
    default:
      break;
  }
  return;
}