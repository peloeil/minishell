#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <libft/ft_stdlib.h>

static void test(int n) {
	char ans[12];
	sprintf(ans, "%d", n);

	char *str = ft_itoa(n);
	if (strcmp(str, ans) != 0) {
		free(str);
		exit(1);
	}
	free(str);
}

int main(void) {
	test(0);
	test(INT_MIN);
	test(INT_MAX);
	for (int i = 0; i < 100; i++) {
		int rnd = rand();
		test(rnd);
		test(-rnd);
	}
}
