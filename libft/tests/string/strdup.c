#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

static void test(const char *str) {
	char *s1 = ft_strdup(str);
	char *s2 = strdup(str);

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

	test(s1);
	test(s2);
	test(s3);
	return 0;
}
