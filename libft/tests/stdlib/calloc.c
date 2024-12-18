#include <stdlib.h>
#include <string.h>
#include <libft/ft_stdlib.h>

static void test(size_t nmemb, size_t size) {
	void *ptr1 = calloc(nmemb, size);
	void *ptr2 = ft_calloc(nmemb, size);
	int diff = memcmp(ptr1, ptr2, nmemb * size);
	free(ptr1);
	free(ptr2);
	if (diff != 0) {
		exit(1);
	}
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		for (size_t j = 0; j < 100; j++) {
			test(i, j);
		}
	}
}
