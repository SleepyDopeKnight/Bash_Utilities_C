.PHONY: all clean test
CC = gcc -std=c11 -D_GNU_SOURCE
CFLAGS = -Wall -Werror -Wextra -o s21_grep
SOURCES = s21_grep.c
OS = $(shell uname -s)

all: s21_grep test check

s21_grep:
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm -rf s21_grep grep.txt grep.txt s21_grep.txt log.txt

test: s21_grep
	chmod +x grep_tests.sh
	./grep_tests.sh

check: s21_grep
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm *.cfg
	cppcheck --enable=all --suppress=missingIncludeSystem ./s21_grep.c
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./s21_grep
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_grep
endif

rebuild: clean all
