FLAGS = -Wall -Wextra -Werror
CC = gcc -std=c11

all: s21_grep

s21_grep: build/main.o build/parser.o build/output.o
	$(CC) $(FLAG) $^ -o s21_grep

build/main.o: main.c grep.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/main.o

build/parser.o: parser.c grep.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/parser.o

build/output.o: output.c grep.h grep.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/output.o

test_grep: build/test.o build/test_grep.o
	$(CC) $(CFLAGS) $^ -o test_grep

build/test_grep.o: tests_grep.c ../common/test_lib.h
	$(CC) $(CFLAGS) -c $< -o build/test_grep.o

build/test.o: ../common/test_lib.c ../common/test_lib.h
	$(CC) $(CFLAGS) -c $< -o build/test.o

clean: 
	rm -rf s21_grep test_grep build
