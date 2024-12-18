#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

#define BUF_SIZE 1000

static void test(void *dst1, void *dst2, int c, size_t len) {
	ft_memset(dst1, c, len);
	memset(dst2, c, len);
	if (memcmp(dst1, dst2, len) != 0) {
		exit(1);
	}
}

int main(void) {
	char dst1[BUF_SIZE];
	char dst2[BUF_SIZE];

	memset(dst1, 'a', BUF_SIZE);
	memset(dst2, 'a', BUF_SIZE);

	for (int i = 0; i < 100; i++) {
		int c = 'a' + rand() % 26;
		size_t len = rand() % 100;
		test(dst1, dst2, c, len);
	}
	return 0;
}
