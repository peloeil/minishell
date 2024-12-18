#include <stdlib.h>
#include <ctype.h>
#include <libft/ft_ctype.h>

static void test(int c) {
	if ((ft_isprint(c) & !isprint(c)) || ((!ft_isprint(c)) & isprint(c))) {
		exit(1);
	}
}

int main(void) {
	for (int c = -1; c < 0xff; c++) {
		test(c);
	}
	return 0;
}

