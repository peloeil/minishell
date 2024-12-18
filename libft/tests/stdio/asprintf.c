#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <libft/ft_stdio.h>

static void test(const char *fmt, char c, char *s, void *p, int d, int i, unsigned int u, unsigned int x, unsigned int X) {
	char *s1 = NULL;
	char *s2 = NULL;
	int byte1 = asprintf(&s1, fmt, c, s, p, d, i, u, x, X);
	int byte2 = ft_asprintf(&s2, fmt, c, s, p, d, i, u, x, X);
	if (byte1 != byte2) {
		free(s1);
		free(s2);
		exit(1);
	}
	if (memcmp(s1, s2, byte1) != 0) {
		free(s1);
		free(s2);
		exit(1);
	}
	free(s1);
	free(s2);
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

	test("\"%c %s %p %d %i %u %x %X\"\n", c, s, p, d, i, u, x, X);
	test("\"%c %s %p %d %i %u %x %X\"\n", CHAR_MIN, s, (void *)0, INT_MIN, INT_MIN, 0, 0, 0);
	test("\"%c %s %p %d %i %u %x %X\"\n", CHAR_MAX, "", (void *)UINTPTR_MAX, INT_MAX, INT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
	test("\"%c %s %p %d %i %u %x %X\"\n", 0, "abc\0efg", p, 0, 0, u, x, X);
	test("\"%%%c%%%s%%%p%%%d%%%i%%%u%%%x%%%X\"\n", c, s, p, d, i, u, x, X);
	return 0;
}

