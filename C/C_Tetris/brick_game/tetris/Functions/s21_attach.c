#include "s21_tetris_backend.h"

void s21_attach() {
  for (int i = 0; i < BLOCKS; i++) {
    int field_x = current_game_state.current_piece.x +
                  current_game_state.current_piece.blocks[i].x;
    int field_y = current_game_state.current_piece.y +
                  current_game_state.current_piece.blocks[i].y;
    int color = pieces[current_game_state.current_piece.type]
                      [current_game_state.current_piece.rotation]
                          .color;
    current_game_state.field[field_y][field_x] = color;
  }
  s21_destroy_rows();
}
