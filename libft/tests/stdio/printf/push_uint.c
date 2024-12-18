#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdio/printf/push_uint.c>

static void test(unsigned int n) {
	char digits[100];
	sprintf(digits, "%u", n);
	if (digit_uint(n) != strlen(digits)) {
		exit(1);
	}
}

int main(void) {
	for (unsigned int i = 0; i < 200000; i++) {
		test(i);
	}
	test(UINT_MAX);
}
