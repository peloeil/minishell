#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libft/ft_string.h>

static void randomize(void *ptr, size_t n) {
	unsigned char *s = ptr;
	for (size_t i = 0; i < n; i++) {
		s[i] = 'a' + rand() % 26;
	}
}

static void test(void *s1, void *s2, size_t n) {
	randomize(s1, n);
	randomize(s2, n);
	ft_bzero(s1, n);
	bzero(s2, n);
	if (memcmp(s1, s2, n) != 0) {
		exit(1);
	}
}

int main(void) {
	char s1[1000];
	char s2[1000];

	test(s1, s2, 10);
	test(s1, s2, 100);
	test(s1, s2, 1000);
	return 0;
}
