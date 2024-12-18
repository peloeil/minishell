#include <stdlib.h>
#include <string.h>
#include <libft/std_string.h>

static void test(void) {
	t_string str;
	ft_str_new(&str);
	if (strlen(str.str) == 0 && str.len == 0 && str.capacity == 0) {
		free(str.str);
	} else {
		exit(1);
	}
}

int main(void) {
	test();
	return 0;
}
