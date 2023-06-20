CC=gcc -Wall -Werror -Wextra -std=c11
UNAME = $(shell uname -s)
SOURCES_TEST = 
OUTNAME = "tests"

ifeq ($(UNAME),Darwin)
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif

all: clean s21_matrix.a test

clean: 
	rm -f *.o *.a *.gcda *.gcov *.gcno *.html *.css tests

s21_matrix.a: s21_matrix.o
	ar -rcs s21_matrix.a *.o s21_matrix.h
	ranlib s21_matrix.a
lib_arm:
	gcc -c -march=armv7-a -mfloat-abi=hard -mfpu=neon -o s21_matrix.o *.c
	ar rcs s21_matrix.a s21_matrix.o

s21_matrix.o: *.c
	$(CC) -c *.c

test: clean s21_matrix_tests.c matrix_tests.o
	$(CC) s21_matrix_tests.c matrix_tests.o $(FLAGS) -o tests
	./tests

matrix_tests.o: s21_matrix.c
	$(CC) -c --coverage s21_matrix.c -o matrix_tests.o

gcov_report:
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html

test_leak: clean
	$(CC) $(FLAGS) -DTEST_LEAK $(SRCS) tests/*.c $(TST_LIBS) -o test
#	$(CC) $(FLAGS) -g -fsanitize=address -DTEST_LEAK tests/*.c $(LIB_NAME).a $(TST_LIBS) -o
check:
	clang-format -n -style=Google *.c *.h tests/*.c tests/*.h

format:
	clang-format -i -style=Google *.c *.h tests/*.c tests/*.h
