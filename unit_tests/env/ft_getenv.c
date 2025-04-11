#include <stdlib.h>
#include <string.h>
#include <minishell/minishell.h>

static void test(const char *key, const char **envp) {
	char *expected = getenv(key);
	char *actual = ft_getenv(key, envp);

	if (expected == NULL && actual != NULL) {
		exit(1);
	}
	if (expected != NULL && actual == NULL) {
		exit(1);
	}
	if (expected == NULL && actual == NULL) {
		return;
	}
	if (strcmp(expected, actual) != 0) {
		exit(1);
	}
}

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	test("PATH", (const char **)envp);
	test("XDG_CONFIG_HOME", (const char **)envp);
	test("USER", (const char **)envp);
	test("KEY", (const char **)envp);
	test("", (const char **)envp);
	return 0;
}
