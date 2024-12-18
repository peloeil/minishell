#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <libft/ft_string.h>

#define BUF_SIZE 1000

static void test(char *buf1, char *buf2, size_t dstsize, ...) {
	va_list ap;
	va_start(ap, dstsize);
	char *str = va_arg(ap, char *);
	if (ft_strlcat(buf1, str, dstsize) != strlcat(buf2, str, dstsize)) {
		exit(1);
	}
	if (memcmp(buf1, buf2, BUF_SIZE) != 0) {
		exit(1);
	}
	va_end(ap);
}

int main(void) {
	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];
	memset(buf1, '\0', BUF_SIZE);
	memset(buf2, '\0', BUF_SIZE);

	const char *s1 = "Hello, world!";
	const char *s2 = "Hello";
	const char *s3 = "";

	for (size_t size = 0; size < BUF_SIZE; size++) {
		test(buf1, buf2, size, s1);
		test(buf1, buf2, size, s2);
		test(buf1, buf2, size, s3);
		test(buf1, buf2, size, s1, s2);
		test(buf1, buf2, size, s1, s2, s3);
		test(buf1, buf2, size, s3, s2, s1);
	}

	return 0;
}
