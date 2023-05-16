#include "s21_cat.h"

int main(int argc, char *argv[]) {
    flag_check(argc, argv);
    for (int i = 1; i < argc; i++) {
        print(i, argv);
    }
    return 0;
}

void print(int i, char *argv[]) {
    char read;
    if (argv[i][0] != '-') {
        FILE *fp;
        fp = fopen(argv[i], "r");
        if (fp != NULL) {
            while (fscanf(fp, "%c", &read) != EOF) {
                flag_b(read);
                flag_e(read);
                flag_n();
                flag_s(read);
                if (flag_v(read) == 0 && flag_t(read) == 0 && read != '\n') printf("%c", read);
                flag.prev_c = read;
            }
            fclose(fp);
        } else {
            printf("s21_cat: %s: No such file or directory\n", argv[i]);
        }
    }
}

void flag_b(char read) {  // work
    if (flag.b && flag.count_b == 1 && read != '\n') {
        printf("%6d\t", flag.count_b);
        flag.count_b++;
    } else if (flag.b && read != '\n' && flag.prev_c == '\n') {
        printf("%6d\t", flag.count_b);
        flag.count_b++;
    }
}

void flag_e(char read) {  // work
    if (flag.e && read == '\n') putchar('$');
}

int flag_s(char read) {
    static int empty_line = 0;
    int res = 0;
    if (flag.s && read == '\n' && empty_line < 2) {
            printf("\n");
            empty_line++;
            res = 1;
    }
        if (flag.s && read == '\n') res = 1;
    if (flag.s == 0 && read == '\n') printf("\n");
    if (flag.prev_c != '\n' && read != '\n') empty_line = 0;
    return res;
}

int flag_t(char read) {  // work
    int res = 0;
    if (flag.t && read == '\t') {
        printf("^I");
        res = 1;
    }
    return res;
}

int flag_n() {   // work
    int res = 0;
    if (flag.n && flag.count_b == 1) {
        printf("%6d\t", flag.count_b);
        flag.count_b++;
    }
    if (flag.n && flag.prev_c == '\n') {
        res = 1;
        printf("%6d\t", flag.count_b);
        flag.count_b++;
    }
    return res;
}

int flag_v(char read) {  // work
    int res = 0;
    if (flag.v && read < 32 && read >= 0 && read != 10 && read != 9) {
        printf("^%c", read + 64);
        res = 1;
    } else if (flag.v && read == 127) {
        printf("^%c", read - 64);
        res = 1;
    }
    return res;
}

void flag_check(int argc, char *argv[]) {
    flag.b = 0;
    flag.e = 0;
    flag.s = 0;
    flag.t = 0;
    flag.n = 0;
    flag.v = 0;
    flag.count_b = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) flag.b = 1;
        if (strcmp(argv[i], "-e") == 0) flag.e = 1;
        if (strcmp(argv[i], "-s") == 0) flag.s = 1;
        if (strcmp(argv[i], "-t") == 0) flag.t = 1;
        if (strcmp(argv[i], "-n") == 0) flag.n = 1;
        if (strcmp(argv[i], "-v") == 0) flag.v = 1;
    }
    if (flag.e || flag.t) flag.v = 1;
}
