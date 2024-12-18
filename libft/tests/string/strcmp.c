#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

static void test(const char *s1, const char *s2) {
	if (ft_strcmp(s1, s2) && !strcmp(s1, s2)) {
		exit(1);
	}
	if ((!ft_strcmp(s1, s2)) && strcmp(s1, s2)) {
		exit(1);
	}
}

int main(void) {
	const char *s1 = "Hello, world!";
	const char *s2 = "Hello";
	const char *s3 = "";

	test(s1, s2);
	test(s2, s3);
	test(s3, s1);

	return 0;
}
