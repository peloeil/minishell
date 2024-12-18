#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_list.h>

static void test(size_t num) {
	t_list *head = NULL;
	for (size_t i = 0; i < num; i++) {
		ft_list_push_back(&head, ft_list_new((void *)i));
		t_list *cur = head;
		for (size_t j = 0; j <= i; j++) {
			if ((uintptr_t)cur->content != (uintptr_t)j) {
				ft_list_clear(&head, NULL);
				exit(1);
			}
			cur = cur->next;
		}
	}
	ft_list_clear(&head, NULL);
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		test(i);
	}
	return 0;
}
