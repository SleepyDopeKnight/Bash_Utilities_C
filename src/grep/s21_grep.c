#include "s21_grep.h"

int main(int argc, char *argv[]) {
    flag_check(argc, argv);
    if (flag.absence) {
        for (int i = 2; i < argc; i++) print(i, argc, argv);
    } else {
        for (int i = 3; i < argc; i++) print(i, argc, argv);
    }
    return 0;
}

void print(int i, int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[i], "r");
    if (fp != NULL) {
        char *str;
        if (flag.absence) {
            str = argv[1];
        } else {
            str = argv[2];
        }
        regex_t regex;
        regcomp(&regex, str, 0);
        char *line = NULL;
        size_t len = 0;
        int zero = 0;
        while (getline(&line, &len, fp) != EOF) {
            int found = regexec(&regex, line, 0, NULL, 0);
            if (flag.absence && found == 0 && argc == 3) {
                printf("%s", line);
            } else if (flag.absence && found == 0 && argc > 3) {
                printf("%s:%s", argv[i], line);
            } else {
            flag_n(line, found, zero, argc, argv, i);
            if (found == 0) flag_c(zero);
            if (flag_l(i, argv, found) == 1) break;
            flag_i(str, regex, line, argc, argv, i);
            flag_v(line, found, argc, argv, i);
            flag_s(line, found, argc, argv, i);
            flag_h(line, found);
            flag_o(regex, line);
            flag_e(line, found, argc, argv, i);
            }
        }
        int count_line = flag_c(zero) - 1;
        if (flag.c && argc == 4) printf("%d\n", count_line);
        if (flag.c && argc  > 4) printf ("%s:%d\n", argv[i], count_line);
        zero = 1;
        flag_c(zero);
        flag_n(line, 0, zero, argc, argv, i);
        regfree(&regex);
        free(line);
        fclose(fp);
    } else {
        if (!flag.s) printf("s21_grep: %s: No such file or directory\n", argv[i]);
    }
}

void flag_n(char *line, int found, int zero, int argc, char *argv[], int i) {
    static int line_count = 1;
    if (flag.n && zero == 0 && found == 0 && argc == 4) printf("%d:%s", line_count, line);
    if (flag.n && zero == 0 && found == 0 && argc > 4) printf("%s:%d:%s", argv[i], line_count, line);
    line_count++;
    if (zero == 1) line_count = 1;
}

int flag_c(int zero) {
    static int line_count = 0;
    if (flag.c && zero == 0) line_count++;
    if (zero == 1) line_count = 0;
    return line_count;
}

int flag_l(int i, char *argv[], int found) {
    int res = 0;
    if (flag.l && found == 0) {
        printf("%s\n", argv[i]);
        res = 1;
    }
    return res;
}

void flag_i(char *str, regex_t regex, char *line, int argc, char *argv[], int i) {
    if (flag.i) {
        regcomp(&regex, str, REG_ICASE);
        int found = regexec(&regex, line, 0, NULL, 0);
        if (found == 0 && argc == 4) printf("%s", line);
        if (found == 0 && argc > 4) printf("%s:%s", argv[i], line);
        regfree(&regex);
    }
}

void flag_v(char *line, int found, int argc, char *argv[], int i) {
    if (flag.v && found == 1 && argc == 4) printf("%s", line);
    if (flag.v && found == 1 && argc > 4) printf("%s:%s", argv[i], line);
}

void flag_e(char *line, int found, int argc, char *argv[], int i) {
    if (flag.e && found == 0 && argc == 4) printf("%s", line);
    if (flag.e && found == 0 && argc > 4) printf("%s:%s", argv[i], line);
}

void flag_o(regex_t regex, char *line) {
    if (flag.o) {
        regmatch_t matchptr;
        size_t len = strlen(line);
        int slip = 0;
        while (regexec(&regex, line + slip, 1, &matchptr, 0) == 0) {
            matchptr.rm_eo += slip;
            matchptr.rm_so += slip;
            if (matchptr.rm_eo > (regoff_t)len) {
                break;
            } else {
                int j = matchptr.rm_so;
                while (j < matchptr.rm_eo) {
                    printf("%c", line[j]);
                    j++;
                }
                printf("\n");
            }
            slip = matchptr.rm_eo;
        }
    }
}

void flag_s(char *line, int found, int argc, char *argv[], int i) {
    if (flag.s && found == 0 && argc == 4) printf("%s", line);
    if (flag.s && found == 0 && argc > 4) printf("%s:%s", argv[i], line);
}

void flag_h(char *line, int found) {
    if (flag.h && found == 0) printf("%s", line);
}

void flag_check(int argc, char *argv[]) {
    flag.e = 0;
    flag.i = 0;
    flag.v = 0;
    flag.c = 0;
    flag.l = 0;
    flag.n = 0;
    flag.o = 0;
    flag.s = 0;
    flag.h = 0;
    flag.absence = 0;

    int count = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            flag.e = 1;
            count++;
        } else if (strcmp(argv[i], "-i") == 0) {
            flag.i = 1;
            count++;
        } else if (strcmp(argv[i], "-v") == 0) {
            flag.v = 1;
            count++;
        } else if (strcmp(argv[i], "-c") == 0) {
            flag.c = 1;
            count++;
        } else if (strcmp(argv[i], "-l") == 0) {
            flag.l = 1;
            count++;
        } else if (strcmp(argv[i], "-n") == 0) {
            flag.n = 1;
            count++;
        } else if (strcmp(argv[i], "-o") == 0) {
            flag.o = 1;
            count++;
        } else if (strcmp(argv[i], "-s") == 0) {
            flag.s = 1;
            count++;
        } else if (strcmp(argv[i], "-h") == 0) {
            flag.h = 1;
            count++;
        } else if (count == 0) {
            flag.absence = 1;
        }
    }
}
