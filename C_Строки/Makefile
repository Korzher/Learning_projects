CC = gcc
LIB_NAME = s21_string.a
CFLAGS = -std=c11 -Wall -Wextra -Werror
CFLAGS_TESTS = $(CFLAGS) -g -I../src
LDFLAGS_TESTS = -lcheck -lm -lpthread -lsubunit
GCOV_FLAGS = --coverage

SRC = s21_memchr.c \
      s21_memcmp.c \
      s21_memcpy.c \
      s21_memset.c \
      s21_strchr.c \
      s21_strcspn.c \
      s21_strerror.c \
      s21_strlen.c \
      s21_strncat.c \
      s21_strncmp.c \
      s21_strncpy.c \
      s21_strpbrk.c \
      s21_strrchr.c \
      s21_strstr.c \
      s21_strtok.c \
      s21_insert.c \
      s21_trim.c \
      s21_to_upper.c \
      s21_to_lower.c \
      s21_sprintf.c

OBJ = $(addprefix build/,$(SRC:.c=.o))
TEST_SRC = tests.c
TEST_OBJ = $(addprefix build/,$(TEST_SRC:.c=.o))
TEST_EXEC = test_all

all: s21_string.a

s21_string.a: $(OBJ)
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
	lcov -t "Report" -c -d ./ --output-file coverage.info --exclude "*/tests.c"
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
