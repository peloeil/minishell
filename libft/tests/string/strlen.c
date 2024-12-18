#include "../test.h"

static void test(const char *str) {
	if (ft_strlen(str) != strlen(str)) {
		exit(1);
	}
}

int main(void) {
	char str[1001];
	memset(str, 'a', 1001);
	for (int i = 0; i < 1000; i++) {
		str[i] = rand() % 26 + 'a';
		str[i + 1] = '\0';
		test(str);
	}
}
