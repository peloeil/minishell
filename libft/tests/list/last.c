#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_list.h>

static void test(size_t num) {
	t_list *head = NULL;
	while (num--) {
		t_list *node = ft_list_new((void *)(uintptr_t)rand());
		ft_list_push_back(&head, node);
	}
	if (num == 0) {
		if (ft_list_last(head) != NULL) {
			exit(1);
		}
		return;
	}
	if ((uintptr_t)ft_list_last(head)->content != (uintptr_t)head->prev->content) {
		ft_list_clear(&head, NULL);
		exit(1);
	}
	ft_list_clear(&head, NULL);
}

int main(void) {
	for (int i = 1; i < 100; i++) {
		test(i);
	}
	return 0;
}
