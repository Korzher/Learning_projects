#include "../common/test_lib.h"

int main() {
  RUN_TEST(test_cat_basic);
  RUN_TEST(test_cat_e_flag);
  RUN_TEST(test_cat_t_flag);
  RUN_TEST(test_cat_s_flag);
  RUN_TEST(test_cat_squeeze_flag);
  RUN_TEST(test_cat_n_flag);
  RUN_TEST(test_cat_number_flag);
  RUN_TEST(test_cat_b_flag);
  RUN_TEST(test_cat_nonblank_flag);
  RUN_TEST(test_cat_etsnb_flag);
  return 0;
}

void test_cat_basic() {
  char* original = run_command("cat cat_test.txt");
  char* custom = run_command("./s21_cat cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "Output differs");

  free(original);
  free(custom);
}

void test_cat_e_flag() {
  char* original = run_command("cat -e cat_test.txt");
  char* custom = run_command("./s21_cat -e cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-e differs");

  free(original);
  free(custom);
}

void test_cat_t_flag() {
  char* original = run_command("cat -t cat_test.txt");
  char* custom = run_command("./s21_cat -t cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-t differs");

  free(original);
  free(custom);
}

void test_cat_s_flag() {
  char* original = run_command("cat -s cat_test.txt");
  char* custom = run_command("./s21_cat -s cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-s differs");

  free(original);
  free(custom);
}

void test_cat_squeeze_flag() {
  char* original = run_command("cat --squeeze-blank cat_test.txt");
  char* custom = run_command("./s21_cat --squeeze-blank cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-squeeze differs");

  free(original);
  free(custom);
}

void test_cat_n_flag() {
  char* original = run_command("cat -n cat_test.txt");
  char* custom = run_command("./s21_cat -n cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-n differs");

  free(original);
  free(custom);
}

void test_cat_number_flag() {
  char* original = run_command("cat -n cat_test.txt");
  char* custom = run_command("./s21_cat --number cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-number differs");

  free(original);
  free(custom);
}

void test_cat_b_flag() {
  char* original = run_command("cat -b cat_test.txt");
  char* custom = run_command("./s21_cat -b cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-b differs");

  free(original);
  free(custom);
}

void test_cat_nonblank_flag() {
  char* original = run_command("cat -b cat_test.txt");
  char* custom = run_command("./s21_cat --number-nonblank cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-t differs");

  free(original);
  free(custom);
}

void test_cat_etsnb_flag() {
  char* original = run_command("cat -etsnb cat_test.txt");
  char* custom = run_command("./s21_cat -etsnb cat_test.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-t differs");

  free(original);
  free(custom);
}
