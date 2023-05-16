.PHONY: all clean test
CC = gcc -std=c11 -D_GNU_SOURCE
CFLAGS = -Wall -Werror -Wextra -o s21_cat
SOURCES = s21_cat.c
OS = $(shell uname -s)

all: s21_cat test check

s21_cat:
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm -rf s21_cat log.txt cat.txt s21_cat.txt 

test: s21_cat
	chmod +x cat_tests.sh
	./cat_tests.sh

check: s21_cat
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm *.cfg
	cppcheck --enable=all --suppress=missingIncludeSystem ./s21_cat.c
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./s21_cat
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_cat
endif

rebuild: clean all
