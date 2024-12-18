#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <libft/ft_stdlib.h>

static void test(const char *str) {

	if (atoi(str) != ft_atoi(str)) {
		exit(1);
	}
}

int main(void) {
	char str[1000];

	test("42");
	test("+42");
	test("-42");
	sprintf(str, "%d", INT_MIN); test(str);
	sprintf(str, "%d", INT_MAX); test(str);
	test("0000001982");
	test("+0000001982");
	test("-0000001982");

	sprintf(str, "%ld", (long)INT_MIN - 1); test(str);
	sprintf(str, "%ld", (long)INT_MAX + 1); test(str);
	sprintf(str, "%u", UINT_MAX); test(str);
	sprintf(str, "%lu", (unsigned long)UINT_MAX + 1); test(str);
	sprintf(str, "%ld", LONG_MAX); test(str);
	sprintf(str, "%ld", LONG_MIN); test(str);
	test("1092837410234987120398471032479");
	test("129384019287340192873401298347123");

	test("");
	test("Hello world!");
	test("+-0000001982");
	test("19284asfd192384");
	return 0;
}
