CC = gcc
CFLAGS = -std=c11 -Werror -Wall -Wextra
CFLAGS_TESTS = $(CFLAGS) -g -I../src -DTEST_MODE
POSTFIX_FLAGS = -lncurses
LDFLAGS_TESTS = -lcheck -lm -lpthread -lsubunit -lncurses -lrt
GCOV_FLAGS = --coverage
DEST_DIR = build/s21_tetris_game
PROJECT_NAME = s21_tetris
VERSION = 1.0.0
DIST_DIR = $(PROJECT_NAME)-$(VERSION)
DIST_ARCHIVE = $(DIST_DIR).tar.gz

SRC = brick_game/tetris/s21_tetris_backend.c \
	  FSM/s21_FSM.c \
	  FSM/s21_game_loop.c \
	  GUI/cli/s21_tetris_frontend.c \

LIB_SRC = brick_game/tetris/s21_tetris_backend.c

TARGET = s21_tetris

OBJ = $(addprefix obj/,$(SRC:.c=.o))
TEST_SRC = test_s21_tetris.c
TEST_OBJ = $(addprefix obj/,$(TEST_SRC:.c=.o))
LIB_OBJ = $(addprefix obj/,$(LIB_SRC:.c=.o))
TEST_EXEC = test_dir/test_all

all: install run

s21_tetris:$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(POSTFIX_FLAGS) -o $(TARGET)

test_dir/s21_tetris.a: $(LIB_OBJ)
	@mkdir -p $(@D)
	ar rcs $@ $^
	ranlib $@

obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: install
	./build/s21_tetris_game/s21_tetris
	

install: s21_tetris
	@mkdir -p $(DEST_DIR)
	touch $(DEST_DIR)/leaderboard.txt
	install -d $(DEST_DIR)
	install -m 755 $(TARGET) $(DEST_DIR)

uninstall:
	rm -f $(TARGET)
	rm -f $(DEST_DIR)/$(TARGET)
	rm -f $(DEST_DIR)/leaderboard.txt
	-@rmdir -p $(DEST_DIR) || true

dvi:
	latex README.tex
	dvipdfmx README.dvi 

dist:
	mkdir -p $(DIST_DIR)
	cp -r brick_game $(DIST_DIR)
	cp -r FSM $(DIST_DIR)
	cp -r GUI $(DIST_DIR)
	cp Makefile $(DIST_DIR)
	cp README.tex $(DIST_DIR)
	cp FSM.png $(DIST_DIR)
	cp s21_defines.h $(DIST_DIR)
	cp s21_objects.h $(DIST_DIR)
	tar -czf $(DIST_ARCHIVE) $(DIST_DIR)
	rm -rf $(DIST_DIR)

test: test_dir/s21_tetris.a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) test_dir/s21_tetris.a $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

gcov_report: 
	@mkdir -p build
	@mkdir -p test_dir
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRC) $(TEST_SRC) $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)
	lcov -t "Report" -c -d ./ --output-file coverage.info --exclude "*/test_s21_tetris.c"
	genhtml coverage.info --output-directory report
	rm -f *.gcda *.gcno

clean:
	rm -f $(TARGET) $(TEST_EXEC) *.a *.gcno *.gcda coverage.info *.aux *.dvi *.log README.pdf *.gz
	rm -rf obj/ test_dir/ report/

cppcheck:
	cppcheck --enable=all --inconclusive --check-config --suppress=missingIncludeSystem $(SRC)

valgrind:
	valgrind --tool=memcheck --leak-check=yes  ./test_dir/test_all

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SRC)

style-check:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(SRC)

.PHONY: all install uninstall test gcov_report clean clang style-check
