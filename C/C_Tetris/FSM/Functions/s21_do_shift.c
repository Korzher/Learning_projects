#include "s21_FSM.h"

void s21_do_shift(settings_t *settings) {
  if (settings->move_direction == LEFT) s21_shift(settings, -1);
  if (settings->move_direction == RIGHT) s21_shift(settings, 1);
  if (settings->move_direction == ROTATE) s21_rotate(settings);
  s21_render_field(settings);
  settings->move_direction = NONE;
  settings->state = MOVING;
}