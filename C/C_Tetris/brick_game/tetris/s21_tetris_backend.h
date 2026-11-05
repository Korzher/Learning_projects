#ifndef S21_TETRIS_H
#define S21_TETRIS_H

#include "../../s21_defines.h"
#include "../../s21_objects.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Рабочие функции
void s21_init_game();
void s21_user_input(UserAction_t action);
int s21_spawn_new_piece();
int s21_is_not_collided(int test_x, int test_y);
void s21_shift(int step);
void s21_rotate();
int s21_move();
void s21_attach();
void s21_calculate_level();
void s21_calculate_speed();
void s21_destroy_rows();
void s21_count_points(int full_rows);
void s21_load_leaderboard();
void s21_update_leaderboard();
void s21_save_leaderboard();
void s21_init_game_info();
void s21_free_game_info();
UserAction_t s21_get_user_input(int signal);

//Функции для тестов
GameInfo_t* s21_test_get_game_state_ptr();
void s21_test_reset_game();

#endif
