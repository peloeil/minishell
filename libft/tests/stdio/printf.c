#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <libft/ft_stdio.h>

static void test(const char *fmt, char c, char *s, void *p, int d, int i, unsigned int u, unsigned int x, unsigned int X) {
	if (      printf(fmt, c, s, p, d, i, u, x, X)
		!= ft_printf(fmt, c, s, p, d, i, u, x, X)) {
		exit(1);
	}
}

int main(void) {
	setvbuf(stdout, NULL, _IOLBF, 0);

	char c = 'a';
	char *s = "hello world";
	void *p = s;
	int d = 42;
	int i = 42;
	unsigned int u = 42;
	unsigned int x = 42;
	unsigned int X = 42;

	test("\"%c %s %p %d %i %u %x %X\"\n", c, s, p, d, i, u, x, X);
	test("\"%c %s %p %d %i %u %x %X\"\n", CHAR_MIN, s, (void *)0, INT_MIN, INT_MIN, 0, 0, 0);
	test("\"%c %s %p %d %i %u %x %X\"\n", CHAR_MAX, "", (void *)UINTPTR_MAX, INT_MAX, INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
	test("\"%c %s %p %d %i %u %x %X\"\n", 0, "abc\0efg", p, 0, 0, u, x, X);
	test("\"%%%c%%%s%%%p%%%d%%%i%%%u%%%x%%%X\"\n", c, s, p, d, i, u, x, X);
	return 0;
}
