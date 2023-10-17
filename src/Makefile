.PHONY: all test s21_matrix_oop.a clang clean cppcheck rebuild
WWW = -Wall -Werror -Wextra -Wpedantic -std=c++17
OS=$(shell uname -s)
LINUX=-lsubunit -lrt
LIBS=-lcheck -lm -lpthread -lgtest -lstdc++ -lgcov --coverage

ifeq ($(OS), Linux)
	OPEN = xdg-open
else
	OPEN = open
endif

all:s21_matrix_oop.a

test: clean_test s21_matrix_oop.a
ifeq ($(OS), Darwin)
	gcc $(WWW) -fprofile-arcs -ftest-coverage -pedantic -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS) 
else
	gcc $(WWW) -fprofile-arcs -ftest-coverage -pedantic -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS) $(LINUX)
endif
	./unit_test

valgrind: clean_test s21_matrix_oop.a
	gcc  $(WWW) -fprofile-arcs -ftest-coverage -pedantic  -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS) $(LINUX)
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./unit_test

leaks: clean_test s21_matrix_oop.a
	gcc  $(WWW) -fprofile-arcs -ftest-coverage -pedantic  -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS) $(LINUX)
	leaks -atExit -- ./unit_test

gcov_report: clean_test s21_matrix_oop.a
ifeq ($(OS), Darwin)
	gcc $(WWW) -fprofile-arcs -ftest-coverage -pedantic -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS)
	./unit_test
	rm s21_matrix_oop_test.gcda s21_matrix_oop_test.gcno
	lcov -t "s21_matrix_test" -o fizzbuzz.info -c -d .
	genhtml -o report fizzbuzz.info
	open report/index.html
else
	gcc  $(WWW) -fprofile-arcs -ftest-coverage -pedantic -g matrix_funk/*.cc tests/*.cc s21_matrix_oop.a -o unit_test $(LIBS) $(LINUX)
	./unit_test
	lcov -t "unit_test" -o test.info -c -d . --include "*matrix_funk/*.cc" --include "*tests/*.cc"
	genhtml -o report test.info
	open report/index.html
endif


s21_matrix_oop.a:
	gcc -c matrix_funk/s21_*.cc
	ar rcs s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a

clang:
	clang-format -style=Google -n matrix_funk/*.cc tests/*.cc *.h

clean_obj:
	rm -rf *.o

clean_lib:
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf *.dSYM

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf unit_test

rebuild: clean all