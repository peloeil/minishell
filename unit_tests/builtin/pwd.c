#include "test_builtin.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char *expected = bash_builtin("pwd", NULL, NULL);
    char *actual = my_builtin(pwd, NULL, NULL);

    if (strcmp(expected, actual) != 0) {
        fprintf(stderr, "NG: pwd command\n");
        fprintf(stderr, "  expected : [%s]\n", expected);
        fprintf(stderr, "  actual: [%s]\n", actual);
        free(expected);
        free(actual);
        return 1;
    }

    printf("OK: pwd command passed (Output: %s)\n", actual);

    free(expected);
    free(actual);
    return 0;
}
