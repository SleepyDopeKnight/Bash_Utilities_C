#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

void print(int i, char *argv[]);
void flag_check(int argc, char *argv[]);
void flag_b(char read);
void flag_e(char read);
int flag_s(char read);
int flag_t(char read);
int flag_n();
int flag_v(char read);

struct flags {
    int b;
    int e;
    int s;
    int t;
    int n;
    int v;
    int count_b;
    char prev_c;
}flag;

#endif  // SRC_CAT_S21_CAT_H_
