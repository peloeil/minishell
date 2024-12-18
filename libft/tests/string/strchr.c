#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libft/ft_string.h>

static void test(const char *str, int ch) {
	if (ft_strchr(str, ch) != strchr(str, ch)) {
		exit(1);
	}
}

int main(void) {
	test("Hello, world!", INT_MIN);
	test("Hello, world!", INT_MAX);
	test("Hello, world!", 'H');
	test("Hello, world!", 'e');
	test("Hello, world!", 'l');
	test("Hello, world!", 'o');
	test("Hello, world!", ',');
	test("Hello, world!", ' ');
	test("Hello, world!", 'w');
	test("Hello, world!", 'r');
	test("Hello, world!", 'd');
	test("Hello, world!", '!');
	test("Hello, world!", '\0');
	for (int i = 0; i < 1000; i++) {
		test("Hello, world!", rand());
	}
	return 0;
}
