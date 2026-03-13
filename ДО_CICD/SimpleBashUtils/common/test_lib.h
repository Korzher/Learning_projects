#ifndef TEST_LIB_H
#define TEST_LIB_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TEST_ASSERT(cond, msg)                                         \
  do {                                                                 \
    if (!(cond)) {                                                     \
      fprintf(stderr, "[FAIL] %s:%d %s\n", __FILE__, __LINE__, (msg)); \
      free(original);                                                  \
      free(custom);                                                    \
      exit(EXIT_FAILURE);                                              \
    }                                                                  \
  } while (0)

#define RUN_TEST(test_func)               \
  do {                                    \
    printf("Running %s... ", #test_func); \
    fflush(stdout);                       \
    test_func();                          \
    printf("[OK]\n");                     \
  } while (0)

char* run_command(const char* cmd);

void test_cat_basic();
void test_cat_e_flag();
void test_cat_t_flag();
void test_cat_s_flag();
void test_cat_squeeze_flag();
void test_cat_n_flag();
void test_cat_number_flag();
void test_cat_b_flag();
void test_cat_nonblank_flag();
void test_cat_etsnb_flag();

void test_grep_basic();
void test_grep_e_flag();
void test_grep_i_flag();
void test_grep_v_flag();
void test_grep_c_flag();
void test_grep_l_flag();
void test_grep_n_flag();
void test_grep_h_single_file();
void test_grep_h_multiple_files();
void test_grep_s_flag();
void test_grep_f_flag();
void test_grep_o_flag();
void test_grep_iv_flag();
void test_grep_no_flag();
void test_grep_oi_flag();
void test_oi_infinite_flag();
void test_grep_ohf_flag();
void test_grep_oinc_flag();
void test_grep_all_flag_multiple_e();

#endif