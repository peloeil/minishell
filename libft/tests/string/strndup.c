#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

static void test(const char *str, size_t n) {
	char *s1 = ft_strndup(str, n);
	char *s2 = strndup(str, n);

	int diff = strcmp(s1, s2);
	free(s1);
	free(s2);
	if (diff != 0) {
		exit(1);
	}
}

int main(void) {
	const char *s1 = "Hello, world!";
	const char *s2 = "Hello";
	const char *s3 = "";

	for (size_t i = 0; i < 1000; i++) {
		test(s1, i);
		test(s2, i);
		test(s3, i);
	}
	return 0;
}

