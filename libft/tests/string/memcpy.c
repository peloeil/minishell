#include <stdlib.h>
#include <string.h>
#include <libft/ft_string.h>

#define BUF_SIZE 1000

static void test(void *dst1, void *dst2, const char *src, size_t n) {
	ft_memcpy(dst1, src, n);
	memcpy(dst2, src, n);
	if (memcmp(dst1, dst2, n) != 0) {
		exit(1);
	}
}

int main(void) {
	char dst1[BUF_SIZE];
	char dst2[BUF_SIZE];
	char src[BUF_SIZE] = "Hello, world!";

	memset(dst1, 'a', BUF_SIZE);
	memset(dst2, 'a', BUF_SIZE);

	for (size_t i = 0; i < BUF_SIZE - 10; i++) {
		test(dst1 + rand() % 10, dst2 + rand() % 10, src, i);
	}

	return 0;
}
