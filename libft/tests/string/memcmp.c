#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

static void test(const void *s1, const void *s2, size_t n) {
	if (ft_memcmp(s1, s2, n) != memcmp(s1, s2, n)) {
		exit(1);
	}
}

int main(void) {
	const char *s1 = "Hello, world!";
	const char *s2 = "Hello";
	const char *s3 = "";

	for (size_t i = 0; i < 100; i++) {
		test(s1, s2, i);
		test(s2, s3, i);
		test(s3, s1, i);
	}
	return 0;
}
