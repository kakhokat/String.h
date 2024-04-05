GCC = gcc
FLAGS = -Wextra -Wall -Werror
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
MAINFILE = s21_string.o
UNAME_S 		:= $(shell uname -s)

CHECKFLAGS= -D_THREAD_SAFE -I/opt/homebrew/Cellar/check/0.15.2/include
OPEN_CMD = open
ADD_LIB =

ifeq ($(UNAME_S),Linux)
	CHECKFLAGS= -lcheck
	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lm -lpthread -lrt -lsubunit
	OS = LINUX
endif

all:
	make s21_string.a
	make test
	make gcov_report

s21_string.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(GCC) $(FLAGS) -c $< $ -o $@

test:
	$(GCC) $(FLAGS) $(CHECKFLAGS) -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck test_files/*.c  *.c -L . $(OBJ) -o $(MAINFILE) $(ADD_LIB)
	./$(MAINFILE)
gcov_report:
	$(GCC) $(FLAGS) $(CHECKFLAGS) -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck --coverage *.c test_files/*.c $(ADD_LIB) -L. $(OBJ) -o rep.o
	./rep.o
	lcov -t "tests" -o tests.info -c -d .
	genhtml -o report tests.info
	$(OPEN_CMD) report/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html /*.cpp /*.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./string_o ./*.dSYM ./test_s21_string