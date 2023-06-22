CC = gcc
CCFLAGS = -Wall -Werror -Wextra -std=c11
UNAME = $(shell uname -s)
DEBUG = -g

ifeq ($(UNAME),Darwin)
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif

all: clean s21_matrix.a

clean: 
	rm -f *.o *.a *.gcda *.gcov *.gcno *.html *.css tests

s21_matrix.a: s21_matrix.o
	ar -rcs s21_matrix.a *.o s21_matrix.h
	ranlib s21_matrix.a

s21_matrix.o:
	$(CC) $(CCFLAGS) -c s21_*.c

test: clean matrix_tests.c matrix_test.o
	$(CC) s21_*.o matrix_tests.c $(FLAGS) -o tests
	./tests

matrix_test.o:
	$(CC) $(CCFLAGS) -c --coverage s21_*.c
	

gcov_report: test
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html
	open coverage_report.html

add_coverage_flag:
	$(eval FLAGS += --coverage)

check:
	clang-format -n -style=Google *.c *.h
format:
	clang-format -i -style=Google *.c *.h
# lib_arm:
# 	gcc -c -march=armv7-a -mfloat-abi=hard -mfpu=neon -o s21_matrix.o *.c
# 	ar rcs s21_matrix.a s21_matrix.o

test_leak: clean
	$(CC) $(CCFLAGS) $(FLAGS) -DTEST_LEAK *.c -o test
#	$(CC) $(FLAGS) -g -fsanitize=address -DTEST_LEAK tests/*.c $(LIB_NAME).a $(TST_LIBS) -o
