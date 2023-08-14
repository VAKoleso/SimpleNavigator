CXX = g++
STD = -std=c++17
CFLAG = -Wall -Wextra -Werror -pedantic
TEST_FILES = test.cpp
FILES = s21_graph.a s21_graph_algorithms.a

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GTEST:= $(shell pkg-config --cflags --libs gtest 2>/dev/null)
	ifeq ($(GTEST),)
		GTEST:=-DGTEST_HAS_PTHREAD=1 -lgtest -pthread
	endif
	LEAKS_CMD = CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes  --leak-check=full --show-leak-kinds=all ./test
endif
ifeq ($(UNAME), Darwin)
	LEAKS_CMD = CK_FORK=no leaks --atExit -- ./test
	GTEST = -fsanitize=address -DGTEST_HAS_PTHREAD=1 -lgtest -pthread
endif

all: clean test

s21_graph.o: clean
	$(CXX) -c $(STD) $(CFLAG) s21_graph.cpp -o s21_graph.o

s21_graph.a: s21_graph.o 
	ar rcs s21_graph.a s21_graph.o

s21_graph_algorithms.o: s21_graph.a
	$(CXX) -c $(STD) $(CFLAG) path.cpp -o path.o
	$(CXX) -c $(STD) $(CFLAG) ant.cpp -o ant.o
	$(CXX) -c $(STD) $(CFLAG) swarm.cpp -o swarm.o
	$(CXX) -c $(STD) $(CFLAG) s21_graph_algorithms.cpp -o s21_graph_algorithms.o

s21_graph_algorithms.a: s21_graph_algorithms.o
	ar rcs s21_graph_algorithms.a s21_graph_algorithms.o path.o ant.o swarm.o

console: clean s21_graph.a s21_graph_algorithms.a
	$(CXX) $(STD) $(CFLAG) main.cpp console_interface.cpp s21_graph.a s21_graph_algorithms.a -o console
	./console

test: s21_graph_algorithms.a
	$(CXX) $(STD) $(CFLAG) -o all_tests $(TEST_FILES) $(GTEST) $(FILES)
	./all_tests

gcov_report: clean
	$(CXX) $(STD) $(CFLAG) -o test $(TEST_FILES) ant.cpp path.cpp s21_graph_algorithms.cpp s21_graph.cpp swarm.cpp $(GTEST) --coverage
	./test || true
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o  *.gc* report *.a test.info \
	*.out *.dSYM console all_tests test *.a *.dot

rebuild: clean all

leaks: test
	CK_FORK=no leaks --atExit -- ./all_tests

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.h *.cpp containers/*.h
	clang-format -n *.h *.cpp containers/*.h
	rm -rf .clang-format

check: leaks clang
