#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <libft/ft_stdio.h>

static void test(int fd, const char *fmt, char c, char *s, void *p, int d, int i, unsigned int u, unsigned int x, unsigned int X) {
	if (      dprintf(fd, fmt, c, s, p, d, i, u, x, X)
		!= ft_dprintf(fd, fmt, c, s, p, d, i, u, x, X)) {
		exit(1);
	}
}

int main(void) {
	setvbuf(stderr, NULL, _IOLBF, 0);

	char c = 'a';
	char *s = "hello world";
	void *p = s;
	int d = 42;
	int i = 42;
	unsigned int u = 42;
	unsigned int x = 42;
	unsigned int X = 42;

	test(STDERR_FILENO, "\"%c %s %p %d %i %u %x %X\"\n", c, s, p, d, i, u, x, X);
	test(STDERR_FILENO, "\"%c %s %p %d %i %u %x %X\"\n", CHAR_MIN, s, (void *)0, INT_MIN, INT_MIN, 0, 0, 0);
	test(STDERR_FILENO, "\"%c %s %p %d %i %u %x %X\"\n", CHAR_MAX, "", (void *)UINTPTR_MAX, INT_MAX, INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
	test(STDERR_FILENO, "\"%c %s %p %d %i %u %x %X\"\n", 0, "abc\0efg", p, 0, 0, u, x, X);
	test(STDERR_FILENO, "\"%%%c%%%s%%%p%%%d%%%i%%%u%%%x%%%X\"\n", c, s, p, d, i, u, x, X);
	return 0;
}
