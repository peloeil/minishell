#include "test_builtin.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *args_array[][MAX_NARGS + 1] = {
        { "No option", "Hello", "World", NULL },
        { "With -n", "-n", "Hello", "World", NULL },
        { "With -n and no newline", "-n", "Hello", "World", NULL },
        { "With -n and empty string", "-n", "", NULL },
        { "With only -n", "-n", NULL },
        { "With only -n and empty string", "-n", "", NULL },
        { "With multiple -n", "-n", "-n", "Hello", "World", NULL },
        { "With multiple -n and no newline", "-n", "-n", "Hello", "World", NULL },
        { "With empty arguments", NULL },
        { "No arguments", NULL },
    };

    size_t total_tests = sizeof(args_array) / sizeof(args_array[0]);
    size_t failed = 0;

    for (size_t i = 0; i < total_tests; i++) {
        char *expected = bash_builtin("echo", args_array[i] + 1, NULL);
        char *actual = my_builtin(echo, args_array[i], NULL);

        if (strcmp(expected, actual) != 0) {
            fprintf(stderr, "NG: %s\n", args_array[i][0]);
            fprintf(stderr, "  expected : [%s]\n", expected);
            fprintf(stderr, "  actual   : [%s]\n", actual);
            failed++;
        }

        free(expected);
        free(actual);
    }

    return (failed == 0 ? 0 : 1);
}
