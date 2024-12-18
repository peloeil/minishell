#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_list.h>

static void test(void *content) {
	t_list *lst = ft_list_new(content);
	if (lst->next != lst || lst->prev != lst || lst->content != content) {
		free(lst);
		exit(1);
	}
	free(lst);
}

int main(void) {
	const char *str = "Hello, world!";
	test((void *)str);
	test(NULL);
	test((void *)1);
	for (int i = 0; i < 10000; i++) {
		test((void *)(uintptr_t)i);
	}
	return 0;
}
