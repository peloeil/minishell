#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libft/ft_string.h>

static void test(const void *str, int ch, size_t n) {
	if (ft_memchr(str, ch, n) != memchr(str, ch, n)) {
		exit(1);
	}
}

int main(void) {
	const char *str = "Hello, world!";
	size_t len = strlen(str);
	for (int i = 0; i < 100; i++) {
		size_t rnd = rand() % (len + 1);
		test(str, rand(), rnd);
		test(str, INT_MIN, rnd);
		test(str, INT_MAX, rnd);
		test(str, 'H', rnd);
		test(str, 'e', rnd);
		test(str, 'l', rnd);
		test(str, 'o', rnd);
		test(str, ',', rnd);
		test(str, ' ', rnd);
		test(str, 'w', rnd);
		test(str, 'r', rnd);
		test(str, 'd', rnd);
		test(str, '!', rnd);
	}
	return 0;
}
