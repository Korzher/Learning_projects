#include "s21_tetris_backend.h"

int s21_spawn_new_piece() {
  current_game_state.current_piece = current_game_state.next_piece;

  int type = rand() % PIECE_COUNT;
  current_game_state.next_piece.type = type;
  current_game_state.next_piece.rotation = 0;
  current_game_state.next_piece.x = FIELD_WIDTH / 2 - 2;
  current_game_state.next_piece.y = 1;

  for (int i = 0; i < BLOCKS; i++) {
    current_game_state.next_piece.blocks[i] = pieces[type][0].blocks[i];
  }

  return s21_is_not_collided(current_game_state.current_piece.x,
                             current_game_state.current_piece.y) == SUCCESS;
}