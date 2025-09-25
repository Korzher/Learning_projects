#ifndef S21_TETRIS_CLI_H
#define S21_TETRIS_CLI_H

#include <string.h>
#include "../../s21_defines.h"
#include "../../s21_objects.h"

void s21_render_start(Windows_t *windows);
void s21_set_name(char *username);
void s21_render_logo(Windows_t *windows);
void s21_render_name(Windows_t *windows);
void s21_render_name_placeholder(Windows_t *windows);
void s21_render_name_register(Windows_t *windows);
void s21_render_field(Windows_t *windows);
void s21_render_next_piece(Windows_t *windows, GameInfo_t game_info);
void s21_render_game_field(Windows_t *windows, GameInfo_t game_info);
void s21_render_ui(Windows_t *windows, GameInfo_t game_info);
void s21_render_pause(Windows_t *windows);
void s21_render_leaderboard(Windows_t *windows, GameInfo_t game_info);
void s21_render_end_game(Windows_t *windows);
void s21_render_final_score(Windows_t *windows);
void s21_render_t(Windows_t *windows, int y, int x);
void s21_render_e(Windows_t *windows, int y, int x);
void s21_render_r(Windows_t *windows, int y, int x);
void s21_render_i(Windows_t *windows, int y, int x);
void s21_render_s(Windows_t *windows, int y, int x);
Piece_t s21_get_piece(int type, int rotation);
GameInfo_t s21_update_current_state();

#endif
