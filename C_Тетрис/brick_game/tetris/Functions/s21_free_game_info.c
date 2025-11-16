#include "s21_tetris_backend.h"

void s21_free_game_info() {
  if (current_game_state.field != NULL) {
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            if (current_game_state.field[i] != NULL) {
                free(current_game_state.field[i]);
                current_game_state.field[i] = NULL;
            }
        }
        free(current_game_state.field);
        current_game_state.field = NULL;
    }
}