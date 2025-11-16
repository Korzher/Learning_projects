#include "../common/test_lib.h"

int main() {
  RUN_TEST(test_grep_basic);
  RUN_TEST(test_grep_e_flag);
  RUN_TEST(test_grep_i_flag);
  RUN_TEST(test_grep_v_flag);
  RUN_TEST(test_grep_c_flag);
  RUN_TEST(test_grep_l_flag);
  RUN_TEST(test_grep_n_flag);
  RUN_TEST(test_grep_h_single_file);
  RUN_TEST(test_grep_h_multiple_files);
  RUN_TEST(test_grep_s_flag);
  RUN_TEST(test_grep_f_flag);
  RUN_TEST(test_grep_o_flag);
  RUN_TEST(test_grep_iv_flag);
  RUN_TEST(test_grep_no_flag);
  RUN_TEST(test_grep_oi_flag);
  RUN_TEST(test_oi_infinite_flag);
  RUN_TEST(test_grep_ohf_flag);
  RUN_TEST(test_grep_oinc_flag);
  RUN_TEST(test_grep_all_flag_multiple_e);
  return 0;
}

void test_grep_basic() {
  char* original = run_command("grep Hello test1.txt");
  char* custom = run_command("./s21_grep Hello test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "Output differs");

  free(original);
  free(custom);
}

void test_grep_e_flag() {
  char* original = run_command("grep -e Hello test1.txt");
  char* custom = run_command("./s21_grep -e Hello test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-e differs");

  free(original);
  free(custom);
}

void test_grep_i_flag() {
  char* original = run_command("grep -i hello test1.txt");
  char* custom = run_command("./s21_grep -i hello test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-i differs");

  free(original);
  free(custom);
}

void test_grep_v_flag() {
  char* original = run_command("grep -v test test1.txt");
  char* custom = run_command("./s21_grep -v test test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-v differs");

  free(original);
  free(custom);
}

void test_grep_c_flag() {
  char* original = run_command("grep -c test test1.txt test2.txt");
  char* custom = run_command("./s21_grep -c test test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-c differs");

  free(original);
  free(custom);
}

void test_grep_l_flag() {
  char* original = run_command("grep -l test test1.txt test2.txt");
  char* custom = run_command("./s21_grep -l test test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-l differs");

  free(original);
  free(custom);
}

void test_grep_n_flag() {
  char* original = run_command("grep -n Another test1.txt test2.txt");
  char* custom = run_command("./s21_grep -n Another test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-n differs");

  free(original);
  free(custom);
}

void test_grep_h_single_file() {
  char* original = run_command("grep -h line test1.txt");
  char* custom = run_command("./s21_grep -h line test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-h with single file differs");

  free(original);
  free(custom);
}

void test_grep_h_multiple_files() {
  char* original = run_command("grep -h line test1.txt test2.txt");
  char* custom = run_command("./s21_grep -h line test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-h with multiple files differs");

  free(original);
  free(custom);
}

void test_grep_s_flag() {
  char* original = run_command("grep -s test nonexist.txt");
  char* custom = run_command("./s21_grep -s test nonexist.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-s differs");

  free(original);
  free(custom);
}

void test_grep_f_flag() {
  char* original = run_command("grep -f patterns.txt test1.txt test2.txt");
  char* custom = run_command("./s21_grep -f patterns.txt test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-f differs");

  free(original);
  free(custom);
}

void test_grep_o_flag() {
  char* original = run_command("grep -o test test1.txt test2.txt");
  char* custom = run_command("./s21_grep -o test test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-o differs");

  free(original);
  free(custom);
}

void test_grep_iv_flag() {
  char* original = run_command("grep -iv hello test1.txt");
  char* custom = run_command("./s21_grep -iv hello test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-iv differs");

  free(original);
  free(custom);
}

void test_grep_no_flag() {
  char* original = run_command("grep -no test test1.txt");
  char* custom = run_command("./s21_grep -no test test1.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-no differs");

  free(original);
  free(custom);
}

void test_grep_oi_flag() {
  char* original = run_command("grep -oi test test1.txt test2.txt");
  char* custom = run_command("./s21_grep -oi test test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-oi differs");

  free(original);
  free(custom);
}

void test_oi_infinite_flag() {
  char* original = run_command("grep -oi e* test1.txt test2.txt");
  char* custom = run_command("./s21_grep -oi e* test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "e* differs");

  free(original);
  free(custom);
}

void test_grep_ohf_flag() {
  char* original = run_command("grep -ohf patterns.txt test1.txt test2.txt");
  char* custom =
      run_command("./s21_grep -ohf patterns.txt test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-ohf differs");

  free(original);
  free(custom);
}

void test_grep_oinc_flag() {
  char* original = run_command("grep -oinc test test1.txt test2.txt");
  char* custom = run_command("./s21_grep -oinc test test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0, "-oinc differs");

  free(original);
  free(custom);
}

void test_grep_all_flag_multiple_e() {
  char* original = run_command(
      "grep -oihlnc -e test -e test -f patterns.txt test1.txt test2.txt");
  char* custom = run_command(
      "./s21_grep -oihlnc -e test -e test -f patterns.txt test1.txt test2.txt");

  TEST_ASSERT(strcmp(original, custom) == 0,
              "all flags with multiple e differs");

  free(original);
  free(custom);
}