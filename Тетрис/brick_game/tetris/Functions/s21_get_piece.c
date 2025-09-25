#include "s21_tetris_backend.h"

Piece_t s21_get_piece(int type, int rotation) { return pieces[type][rotation]; }