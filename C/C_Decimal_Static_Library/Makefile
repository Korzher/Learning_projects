CC = gcc
LIB_NAME = s21_decimal.a
CFLAGS = -std=c11 -Wall -Wextra -Werror
CFLAGS_TESTS = $(CFLAGS) -g -I../src
LDFLAGS_TESTS = -lcheck -lm -lpthread -lsubunit
GCOV_FLAGS = --coverage

SRC = s21_add.c \
	s21_add_same_sign.c \
	s21_add_diff_sign.c \
	s21_bank_round.c \
	s21_compare.c \
	s21_div.c \
	s21_divide_by_ten.c \
	s21_floor.c \
	s21_fmodl.c \
	s21_from_decimal_to_float.c \
	s21_from_decimal_to_int.c \
	s21_from_float_to_decimal.c \
	s21_from_int_to_decimal.c \
	s21_get_scale.c \
	s21_get_sign.c \
	s21_highest_bit.c \
	s21_increase_scale.c \
	s21_is_valid.c \
	s21_is_zero.c \
	s21_mul.c \
	s21_multiply_by_ten_with_add.c \
	s21_negate.c \
	s21_normalize_scale.c \
	s21_round.c \
	s21_roundl.c \
	s21_set_scale.c \
	s21_set_sign.c \
	s21_shift_left.c \
	s21_shift_right.c \
	s21_simple_div.c \
	s21_simple_mul.c \
	s21_sub.c \
	s21_subtract_raw_bits.c \
	s21_truncate.c

OBJ = $(addprefix build/,$(SRC:.c=.o))
TEST_SRC = test_s21_decimal.c
TEST_OBJ = $(addprefix build/,$(TEST_SRC:.c=.o))
TEST_EXEC = test_all

all: s21_decimal.a

s21_decimal.a: $(OBJ)
	ar rcs $@ $^
	ranlib $@

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS_TESTS) $(TEST_OBJ) $(LIB_NAME) $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

gcov_report: $(LIB_NAME)
	@mkdir -p build
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -L. $(LIB_NAME) $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)
	lcov -t "Report" -c -d ./ --output-file coverage.info --exclude "*/test_s21_decimal.c"
	genhtml coverage.info --output-directory report
	rm -f *.gcda *.gcno

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SRC) $(TEST_SRC)

style-check:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(SRC) $(TEST_SRC)

clean:
	rm -rf build *.a *.gc* $(TEST_EXEC) report coverage.info

.PHONY: all clean test gcov_report open_report valgrind clang style-check
