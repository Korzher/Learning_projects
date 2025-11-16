CC = gcc
LIB_NAME = s21_matrix.a
CFLAGS = -std=c11 -Wall -Wextra -Werror
CFLAGS_TESTS = $(CFLAGS) -g -I../src
LDFLAGS_TESTS = -lcheck -lm -lpthread -lsubunit -Wl,-wrap=calloc -ldl
GCOV_FLAGS = --coverage

SRC = s21_calc_complements.c \
	s21_create_matrix.c \
	s21_determinant.c \
	s21_eq_matrix.c \
	s21_fabs.c \
	s21_invalid_matrix.c \
	s21_inverse_matrix.c \
	s21_minor_matrix.c \
	s21_mult_matrix.c \
	s21_mult_number.c \
	s21_remove_matrix.c \
	s21_size_comp.c \
	s21_sub_matrix.c \
	s21_sum_matrix.c \
	s21_transpose.c \


OBJ = $(addprefix build/,$(SRC:.c=.o))
TEST_SRC = test_s21_matrix.c
TEST_OBJ = $(addprefix build/,$(TEST_SRC:.c=.o))
TEST_EXEC = test_all

all: s21_matrix.a

s21_matrix.a: $(OBJ)
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
	lcov -t "Report" -c -d ./ --output-file coverage.info --exclude "*/test_s21_matrix.c"
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
