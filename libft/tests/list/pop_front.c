#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_list.h>

static void test(size_t num) {
	t_list *head = NULL;
	for (size_t i = 0; i < num; i++) {
		t_list *node = ft_list_new((void *)(uintptr_t)rand());
		ft_list_push_back(&head, node);
	}
	for (size_t i = 0; i < num; i++) {
		t_list *expected = head;
		t_list *actual = ft_list_pop_front(&head);
		if (actual != expected) {
			ft_list_delete(actual, NULL);
			ft_list_clear(&head, NULL);
			exit(1);
		}
		ft_list_delete(actual, NULL);
	}
	t_list *last = ft_list_pop_back(&head);
	if (last != NULL) {
		ft_list_delete(last, NULL);
		ft_list_clear(&head, NULL);
		exit(1);
	}
	ft_list_delete(last, NULL);
	ft_list_clear(&head, NULL);
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		test(i);
	}
	return 0;
}

