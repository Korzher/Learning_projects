CXX = g++
CXXFLAGS = -std=c++20 -Werror -Wall -Wextra
CXXFLAGS_TESTS = $(CXXFLAGS) -g
LDFLAGS_TESTS  = -lgtest -lgtest_main -pthread 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

SRC = s21_matrix_oop.cpp

OBJ = $(addprefix build/,$(SRC:.cpp=.o))
TEST_SRC = test_s21_matrix_oop.cpp
TEST_OBJ = $(addprefix build/,$(TEST_SRC:.cpp=.o))
TEST_EXEC = test_all

all: s21_matrix_oop.a

s21_matrix_oop.a: $(OBJ)
	ar rcs $@ $^

build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJ) s21_matrix_oop.a 
	$(CXX) $(CXXFLAGS_TESTS) $(TEST_OBJ) s21_matrix_oop.a $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

gcov_report: 
	@mkdir -p build
	@mkdir -p test_dir
	$(CXX) $(CXXFLAGS_TESTS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	./$(TEST_EXEC)
		lcov -t "Report" -c -d ./ --output-file coverage.info \
		--exclude "*/test_*.cpp" \
		--exclude "/usr/include/*" \
		--exclude "/usr/lib/*" \
		--exclude "*/gtest/*" \
		--ignore-errors mismatch,unused
	genhtml coverage.info --output-directory report
	rm -f *.gcda *.gcno

valgrind: $(TEST_OBJ) s21_matrix_oop.a
	$(CXX) $(CXXFLAGS_TESTS) $(TEST_OBJ) s21_matrix_oop.a $(LDFLAGS_TESTS) -o $(TEST_EXEC)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC) --gtest_filter="-*BadAlloc*"

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SRC) $(TEST_SRC)

style-check:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(SRC) $(TEST_SRC)

clean:
	rm -rf build test_dir *.a *.gc* $(TEST_EXEC) report coverage.info

.PHONY: all test gcov_report valgrind clang style-check clean