#include "s21_tetris_backend.h"

void s21_rotate() {
  CurrentPiece_t original = current_game_state.current_piece;
  int new_rotation =
      (current_game_state.current_piece.rotation + 1) % ROTATIONS;
  Piece_t new_piece =
      pieces[current_game_state.current_piece.type][new_rotation];

  for (int i = 0; i < BLOCKS; i++) {
    current_game_state.current_piece.blocks[i] = new_piece.blocks[i];
  }

  current_game_state.current_piece.rotation = new_rotation;

  if (!(s21_is_not_collided(current_game_state.current_piece.x,
                            current_game_state.current_piece.y) == SUCCESS)) {
    current_game_state.current_piece = original;
  }
}