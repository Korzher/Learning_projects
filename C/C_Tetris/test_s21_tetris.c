#include <check.h>
#include <unistd.h>

#include "brick_game/tetris/s21_tetris_backend.h"
#include "GUI/cli/s21_tetris_frontend.h"
#include "FSM/s21_FSM.h"
#include "s21_defines.h"
#include "s21_objects.h"

#define TEST_FILENAME "leaderboard.txt"

START_TEST(test_s21_set_name) {
    s21_test_reset_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    
    s21_set_name("test_name");

    ck_assert_str_eq(state->name, "test_name");
}
END_TEST

START_TEST(test_s21_set_name_anon) {
    s21_test_reset_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    
    s21_set_name("");

    ck_assert_str_eq(state->name, "Anonim");
}
END_TEST

START_TEST(test_s21_game_initialization) {
    s21_test_reset_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    
    ck_assert_int_eq(state->score, 0);
    ck_assert_int_eq(state->level, 1);
    ck_assert_int_eq(state->next_piece.type, -1);
    ck_assert_ptr_null(state->field);
}
END_TEST

START_TEST(test_s21_game_current_state) {
    s21_test_reset_game();
    GameInfo_t state = s21_update_current_state();
    
    ck_assert_int_eq(state.score, 0);
    ck_assert_int_eq(state.level, 1);
    ck_assert_int_eq(state.next_piece.type, -1);
    ck_assert_ptr_null(state.field);
}
END_TEST

START_TEST(test_s21_get_piece) {
    s21_test_reset_game();
    Piece_t piece = s21_get_piece(1, 1);
    

    ck_assert_int_eq(piece.color, 2);
}
END_TEST

START_TEST(test_s21_init_game) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_init_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    

    ck_assert_int_eq(state->field[3][3], 0);
    ck_assert_int_eq(state->field[0][0], -1);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_spawn_new) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_spawn_new_piece();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    

    ck_assert_int_ne(state->next_piece.type, -1);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_is_not_collided_x) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_spawn_new_piece();
    s21_spawn_new_piece();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    state->current_piece.blocks[0].x = 5;
    state->current_piece.blocks[0].y = 5;
    state->field[5][5] = 3;
    int result = s21_is_not_collided(5, 5);

    ck_assert_int_eq(result, 1);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_is_not_collided_y) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_spawn_new_piece();
    s21_spawn_new_piece();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    state->current_piece.blocks[0].x = 5;
    state->current_piece.blocks[0].y = 5;
    state->field[5][5] = 3;
    int result = s21_is_not_collided(0, 0);

    ck_assert_int_eq(result, 1);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_shift) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    state->current_piece.blocks[0].x = 5;
    state->current_piece.blocks[0].y = 5;
    state->field[5][5] = 3;
    s21_shift(1);

    ck_assert_int_ne(state->current_piece.blocks[0].x, 0);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_shift_fail) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    state->current_piece.blocks[0].x = 4;
    state->current_piece.blocks[0].y = 5;
    state->current_piece.y = 5;
    state->field[5][5] = 3;
    s21_shift(1);

    ck_assert_int_ne(state->current_piece.blocks[0].x, 0);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_rotate) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    s21_spawn_new_piece();
    s21_spawn_new_piece();
    s21_move();
    s21_move();
    s21_rotate();

    ck_assert_int_eq(state->current_piece.rotation, 1);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_attach) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();

    Piece_t piece = s21_get_piece(3, 0);
    
    state->current_piece.type = 3;
    state->current_piece.rotation = 0;
    state->current_piece.x = 8;
    state->current_piece.y = 10;
    
    for (int i = 0; i < BLOCKS; i++) {
        state->current_piece.blocks[i].x = piece.blocks[i].x;
        state->current_piece.blocks[i].y = piece.blocks[i].y;
    }

    s21_attach();

    ck_assert_int_eq(state->field[10][8], O);
    ck_assert_int_eq(state->field[10][9], O);
    ck_assert_int_eq(state->field[11][8], O);
    ck_assert_int_eq(state->field[11][9], O);
    
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_destroy_rows_single_full_row) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_init_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();

    for (int x = 1; x < FIELD_WIDTH - 1; x++) {
        state->field[18][x] = 1;
    }


    s21_destroy_rows();

    for (int x = 1; x < FIELD_WIDTH - 1; x++) {
        ck_assert_int_eq(state->field[18][x], 0);
    }
    
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_destroy_rows_multiple_full_rows) {
    s21_test_reset_game();
    s21_init_game_info();
    s21_init_game();
    GameInfo_t* state = s21_test_get_game_state_ptr();

    for (int y = 17; y <= 18; y++) {
        for (int x = 1; x < FIELD_WIDTH - 1; x++) {
            state->field[y][x] = 1;
        }
    }

    state->field[15][7] = 3;
    state->field[16][5] = 2;

    s21_destroy_rows();

    for (int y = 17; y <= 18; y++) {
        for (int x = 1; x < FIELD_WIDTH - 1; x++) {
            if (!(y == 17 && x == 7) && !(y == 18 && x == 5)) {
                ck_assert_int_eq(state->field[y][x], 0);
            }
        }
    }
    
    ck_assert_int_eq(state->field[17][7], 3);
    ck_assert_int_eq(state->field[18][5], 2);
    
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_scores) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();

    s21_count_points(3);
    ck_assert_int_eq(state->score, 700);

    s21_count_points(4);
    ck_assert_int_eq(state->score, 2200);

    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_level) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    state->score = 7500;
    s21_calculate_level();
    ck_assert_int_eq(state->level, 10);

    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_load_leaderboard_valid_file) {
    s21_test_reset_game();
    s21_init_game_info();
    FILE *file = fopen(FILENAME, "w");
    ck_assert_ptr_nonnull(file);
    fprintf(file, "Player1 10000\nPlayer2 5000\nPlayer3 2500\n");
    fclose(file);
    GameInfo_t* state = s21_test_get_game_state_ptr();

    strncpy(state->name, "Current", sizeof(state->name));
    state->score = 3000;

    s21_load_leaderboard();

    ck_assert_int_eq(state->leaderboard_size, 4);
    ck_assert_int_eq(state->leaderboard_pos, 3);

    ck_assert_str_eq(state->leaderboard[0].name, "Player1");
    ck_assert_int_eq(state->leaderboard[0].score, 10000);

    unlink(FILENAME);
    s21_free_game_info();
}

START_TEST(test_s21_save_leaderboard) {
    unlink(FILENAME);
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();

    state->leaderboard_size = 3;

    strncpy(state->leaderboard[0].name, "PlayerA", sizeof(state->leaderboard[0].name));
    state->leaderboard[0].score = 12000;

    strncpy(state->leaderboard[1].name, "PlayerB", sizeof(state->leaderboard[1].name));
    state->leaderboard[1].score = 8000;

    strncpy(state->leaderboard[2].name, "PlayerC", sizeof(state->leaderboard[2].name));
    state->leaderboard[2].score = 4500;

    s21_save_leaderboard();

    FILE *file = fopen(FILENAME, "r");
    ck_assert_ptr_nonnull(file);

    char name[11];
    int score;
    int count = 0;
    while (fscanf(file, "%10s %d", name, &score) == 2) {
        ck_assert_str_eq(name, state->leaderboard[count].name);
        ck_assert_int_eq(score, state->leaderboard[count].score);
        count++;
    }
    ck_assert_int_eq(count, state->leaderboard_size);

    fclose(file);
    unlink(FILENAME);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_update_leaderboard) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    strncpy(state->leaderboard[0].name, "Player1", 11);
    state->leaderboard[0].score = 5000;

    strncpy(state->leaderboard[1].name, "Player2", 11);
    state->leaderboard[1].score = 3000;

    strncpy(state->leaderboard[2].name, "Player3", 11);
    state->leaderboard[2].score = 1000;

    state->leaderboard_pos = 2;

    state->score = 4000;

    s21_update_leaderboard();

    ck_assert_int_eq(state->leaderboard_pos, 1);

    ck_assert_str_eq(state->leaderboard[0].name, "Player1");
    ck_assert_int_eq(state->leaderboard[0].score, 5000);

    ck_assert_str_eq(state->leaderboard[1].name, "Player3");
    ck_assert_int_eq(state->leaderboard[1].score, 4000);

    ck_assert_str_eq(state->leaderboard[2].name, "Player2");
    ck_assert_int_eq(state->leaderboard[2].score, 3000);
    s21_free_game_info();
}
END_TEST


START_TEST(test_s21_do_start) {
    GameState state = GAME_START;
    s21_do_game_start(Start, &state);
    ck_assert_int_eq(state, NAME_INSERT);
}
END_TEST


START_TEST(test_s21_do_spawn) {
    s21_test_reset_game();
    s21_init_game_info();
    GameState state = NAME_INSERT;
    s21_do_spawn(&state);
    ck_assert_int_eq(state, MOVING);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_do_attach) {
    s21_test_reset_game();
    s21_init_game_info();
    GameState state = NAME_INSERT;
    s21_do_attach(&state);
    ck_assert_int_eq(state, SPAWN);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_do_moving) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    s21_spawn_new_piece();
    s21_spawn_new_piece();
    s21_move();
    s21_move();
    GameState game_state = MOVING;


    s21_do_moving(Left, &game_state);
    ck_assert_int_eq(game_state, SHIFT);
    game_state = MOVING;

    s21_do_moving(Right, &game_state);
    ck_assert_int_eq(game_state, SHIFT);
    game_state = MOVING;

    s21_do_moving(Action, &game_state);
    ck_assert_int_eq(game_state, SHIFT);
    game_state = MOVING;

    s21_do_moving(Pause, &game_state);
    ck_assert_int_eq(game_state, PAUSE);
    game_state = MOVING;

    s21_do_moving(Terminate, &game_state);
    ck_assert_int_eq(game_state, GAME_OVER);

    ck_assert_ptr_nonnull(state->field);
    s21_free_game_info();
}
END_TEST

START_TEST(test_s21_get_user_input_enter) {
    ck_assert_int_eq(s21_get_user_input(ENTER_KEY), Start);
}
END_TEST

START_TEST(test_s21_get_user_input_w) {
    ck_assert_int_eq(s21_get_user_input('w'), Up);
    ck_assert_int_eq(s21_get_user_input('W'), Up);
}
END_TEST

START_TEST(test_s21_get_user_input_s) {
    ck_assert_int_eq(s21_get_user_input('s'), Down);
    ck_assert_int_eq(s21_get_user_input('S'), Down);
}
END_TEST

START_TEST(test_s21_get_user_input_a) {
    ck_assert_int_eq(s21_get_user_input('a'), Left);
    ck_assert_int_eq(s21_get_user_input('A'), Left);
}
END_TEST

START_TEST(test_s21_get_user_input_d) {
    ck_assert_int_eq(s21_get_user_input('d'), Right);
    ck_assert_int_eq(s21_get_user_input('D'), Right);
}
END_TEST

START_TEST(test_s21_get_user_input_space) {
    ck_assert_int_eq(s21_get_user_input(' '), Action);
}
END_TEST

START_TEST(test_s21_get_user_input_q) {
    ck_assert_int_eq(s21_get_user_input('q'), Terminate);
    ck_assert_int_eq(s21_get_user_input('Q'), Terminate);
}
END_TEST

START_TEST(test_s21_get_user_input_p) {
    ck_assert_int_eq(s21_get_user_input('p'), Pause);
    ck_assert_int_eq(s21_get_user_input('P'), Pause);
}
END_TEST


START_TEST(test_s21_memory_management) {
    s21_test_reset_game();
    s21_init_game_info();
    GameInfo_t* state = s21_test_get_game_state_ptr();
    ck_assert_ptr_nonnull(state->field);
    
    s21_test_reset_game();
    s21_test_get_game_state_ptr();
    ck_assert_ptr_null(state->field);
    s21_free_game_info();
}
END_TEST

SRunner *create_runner() {
  SRunner *sr;
  Suite *s21_tetris;
  TCase *tc_s21_tetris_machanics;


  s21_tetris = suite_create("tetris");

  sr = srunner_create(s21_tetris);

  tc_s21_tetris_machanics = tcase_create("mechanics");
  tcase_add_test(tc_s21_tetris_machanics, test_s21_set_name);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_set_name_anon);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_game_initialization);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_memory_management);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_game_current_state);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_piece);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_init_game);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_spawn_new);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_is_not_collided_x);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_is_not_collided_y);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_shift);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_shift_fail);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_rotate);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_attach);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_destroy_rows_single_full_row);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_destroy_rows_multiple_full_rows);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_scores);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_level);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_load_leaderboard_valid_file);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_save_leaderboard);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_update_leaderboard);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_do_start);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_do_spawn);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_do_moving);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_do_attach);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_enter);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_w);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_s);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_a);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_d);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_space);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_q);
  tcase_add_test(tc_s21_tetris_machanics, test_s21_get_user_input_p);

  suite_add_tcase(s21_tetris, tc_s21_tetris_machanics);

  return sr;
}


int main() {
  SRunner *sr = create_runner();
  srunner_run_all(sr, CK_NORMAL);
  int failed_quantity = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_quantity == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
