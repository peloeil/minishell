#include <stdlib.h>
#include <libft/ft_list.h>

static void test(size_t size) {
	t_list *head = NULL;
	for (size_t i = 0; i < size; i++) {
		ft_list_push_back(&head, ft_list_new((void *)size));
	}

	size_t res = ft_list_size(head);
	ft_list_clear(&head, NULL);
	if (res != size) {
		exit(1);
	}
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		test(i);
	}
	return 0;
}
