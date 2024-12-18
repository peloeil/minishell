#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <libft/ft_stdio.h>

#define BUF_SIZE 1000

static void test(char *buf1, char *buf2, size_t size, const char *fmt, char c, char *s, void *p, int d, int i, unsigned int u, unsigned int x, unsigned int X) {
	if (      snprintf(buf1, size, fmt, c, s, p, d, i, u, x, X)
		!= ft_snprintf(buf2, size, fmt, c, s, p, d, i, u, x, X)) {
		exit(1);
	}
	if (memcmp(buf1, buf2, BUF_SIZE) != 0) {
		exit(1);
	}
}

int main(void) {
	char c = 'a';
	char *s = "hello world";
	void *p = s;
	int d = 42;
	int i = 42;
	unsigned int u = 42;
	unsigned int x = 42;
	unsigned int X = 42;

	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];
	memset(buf1, 'a', 1000);
	memset(buf2, 'a', 1000);

	test(buf1, buf2, 20, "\"%c %s %p %d %i %u %x %X\"\n", c, s, p, d, i, u, x, X);
	test(buf1, buf2, 50, "\"%c %s %p %d %i %u %x %X\"\n", CHAR_MIN, s, (void *)0, INT_MIN, INT_MIN, 0, 0, 0);
	test(buf1, buf2, 100, "\"%c %s %p %d %i %u %x %X\"\n", CHAR_MAX, "", (void *)UINTPTR_MAX, INT_MAX, INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
	test(buf1, buf2, BUF_SIZE - 1, "\"%c %s %p %d %i %u %x %X\"\n", 0, "abc\0efg", p, 0, 0, u, x, X);
	test(buf1, buf2, BUF_SIZE, "\"%c %s %p %d %i %u %x %X\"\n", 0, "abc\0efg", p, 0, 0, u, x, X);
	test(buf1, buf2, BUF_SIZE, "\"%%%c%%%s%%%p%%%d%%%i%%%u%%%x%%%X\"\n", c, s, p, d, i, u, x, X);
	return 0;
}
