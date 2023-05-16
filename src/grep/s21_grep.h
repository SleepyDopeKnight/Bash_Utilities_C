#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void print(int i,  int argc, char *argv[]);
void flag_check(int argc, char *argv[]);
void flag_n(char *line, int found, int zero, int argc, char *argv[], int i);
int flag_c(int zero);
int flag_l(int i, char *argv[], int found);
void flag_i(char *str, regex_t regex, char *line, int argc, char *argv[], int i);
void flag_v(char *line, int found, int argc, char *argv[], int i);
void flag_e(char *line, int found, int argc, char *argv[], int i);
void flag_o(regex_t regex, char *line);
void flag_s(char *line, int found, int argc, char *argv[], int i);
void flag_h(char *line, int found);

struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int o;
    int s;
    int h;
    int absence;
}flag;

#endif  // SRC_GREP_S21_GREP_H_
