#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void test(const char *key, const t_envp *envp) {
    char *expected = getenv(key);
    char *actual = ft_getenv(key, envp);

    if (expected == NULL && actual != NULL) {
        printf("Error: expected NULL for key '%s', got '%s'\n", key, actual);
        free_ms_envp((t_envp *)envp);
        exit(1);
    }
    if (expected != NULL && actual == NULL) {
        printf("Error: expected '%s' for key '%s', got NULL\n", expected, key);
        free_ms_envp((t_envp *)envp);
        exit(1);
    }
    if (expected == NULL && actual == NULL) { return; }
    if (strcmp(expected, actual) != 0) {
        printf("Error: expected '%s' for key '%s', got '%s'\n", expected, key, actual);
        free_ms_envp((t_envp *)envp);
        exit(1);
    }
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;

    t_envp *env = make_ms_envp(envp);

    test("PATH", env);
    test("XDG_CONFIG_HOME", env);
    test("USER", env);
    test("KEY", env);

    free_ms_envp((t_envp *)env);
    return 0;
}
