FLAGS = -Wall -Wextra -Werror
CC = gcc -std=c99

all: s21_cat

s21_cat: build/main.o build/parser.o build/reader.o
	$(CC) $(FLAGS) $^ -o s21_cat

build/main.o: main.c cat.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/main.o

build/parser.o: parser.c cat.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/parser.o

build/reader.o: reader.c cat.h
	@mkdir -p build
	$(CC) $(FLAGS) -c $< -o build/reader.o

test_cat: build/test.o build/test_cat.o
	$(CC) $(CFLAGS) $^ -o test_cat

build/test_cat.o: tests_cat.c ../common/test_lib.h
	$(CC) $(CFLAGS) -c $< -o build/test_cat.o

build/test.o: ../common/test_lib.c ../common/test_lib.h
	$(CC) $(CFLAGS) -c $< -o build/test.o

clean: 
	rm -rf s21_cat test_cat build
