#include "s21_tetris_backend.h"

void s21_set_name(char *username) {
  if (strlen(username) != 0) {
    strncpy(current_game_state.name, username, 11);
  } else {
    strncpy(current_game_state.name, "Anonim", 7);
  }
}