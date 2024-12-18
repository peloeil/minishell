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
		char *s = va_arg(ap, char *);
		ft_str_push_str(&str, s);
	}
	va_end(ap);
	if (memcmp(ans, str.str, str.len + 1) == 0) {
		free(str.str);
	} else {
		exit(1);
	}
}

int main(void) {
	test(4, "Hello, world!", "Hello", ",", " world", "!");
	test(4, "I have a pen", "I", " have", " a", " pen");
	return 0;
}

