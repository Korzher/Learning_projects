#include "s21_FSM.h"

UserAction_t s21_get_user_input(int signal) {
  UserAction_t action = NO_INPUT;

  if (signal == ENTER_KEY)
    action = Start;
  else if (signal == 'w' || signal == 'W')
    action = Up;
  else if (signal == 's' || signal == 'S')
    action = Down;
  else if (signal == 'a' || signal == 'A')
    action = Left;
  else if (signal == 'd' || signal == 'D')
    action = Right;
  else if (signal == ' ')
    action = Action;
  else if (signal == 'q' || signal == 'Q')
    action = Terminate;
  else if (signal == 'p' || signal == 'P')
    action = Pause;

  return action;
}