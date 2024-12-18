#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <libft/std_string.h>

static void test(int num, const char *ans, ...) {
	t_string str;
	ft_str_new(&str);

	va_list ap;
	va_start(ap, ans);
	for (int i = 0; i < num; i++) {
		char ch = va_arg(ap, int);
		ft_str_push(&str, ch);
	}
	va_end(ap);
	if (memcmp(ans, str.str, num + 1) == 0) {
		free(str.str);
	} else {
		exit(1);
	}
}

int main(void) {
	test(4, "abcd", 'a', 'b', 'c', 'd');
	test(4, "\0bcd", '\0', 'b', 'c', 'd');
	test(4, "a\0cd", 'a', '\0', 'c', 'd');
	test(4, "ab\0d", 'a', 'b', '\0', 'd');
	test(4, "abc\0", 'a', 'b', 'c', '\0');
	return 0;
}
