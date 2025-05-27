#include "test_builtin.c"
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdlib.h>
#include <string.h>

static size_t next_len(const char *str, size_t start) {
    size_t len = 0;
    while (str[start + len] != '\0' && str[start + len] != '\n') {
        len++;
    }
    return len;
}

static void test(char **argv, t_envp **envp) {
    char *expected = bash_builtin("export", argv + 1, envp);
    char *actual = my_builtin(export, argv, envp);

    int cmp = 0;
    size_t index = 0;
    while (expected[index] != '\0' && actual[index] != '\0') {
        size_t len = next_len(expected, index);
        if (len > next_len(actual, index)) { len = next_len(actual, index); }
        if (len == 0) { break; }
        int tmp = strncmp(expected + index, actual + index, len);
        if (tmp != 0) {
            printf("expected: %.*s\n", (int)len, expected + index);
            printf("actual  : %.*s\n", (int)len, actual + index);
            cmp = tmp;
        }
        index += len;
    }
    free(expected);
    free(actual);
    if (cmp != 0) { exit(1); }
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;

    char *args_array[][MAX_NARGS + 1] = {
        { "argv[0]", NULL },
        { "argv[0]", "a", NULL },
        { "argv[0]", "a=b", NULL },
        { "argv[0]", "a=b", "c=d", NULL },
		{ "argv[0]", "1a=b", NULL },
        { "argv[0]", "!a=b", NULL },
        { "argv[0]", "_a=b", "c=d", NULL },
        { "argv[0]", "!a",  NULL },
        { "argv[0]", "a!aa=b", NULL },
        { "argv[0]", "a=!b", "c=d", NULL },
        { "argv[0]", "a_=b", "c_=d", NULL },
    };

    t_envp *ms_envp;
    make_ms_envp(&ms_envp, envp);

    printf("=== export ===\n");
    int ntests = sizeof(args_array) / sizeof(args_array[0]);
    for (int i = 0; i < ntests; i++) {
        test(args_array[i], &ms_envp);
    }

    free_ms_envp(ms_envp);
    return 0;
}
