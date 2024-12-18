#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_list.h>

static void test(size_t num) {
	t_list *head = NULL;
	for (size_t i = 0; i < num; i++) {
		ft_list_push_front(&head, ft_list_new((void *)i));
		t_list *cur = head;
		for (size_t j = i + 1; j >= 1; j--) {
			if ((uintptr_t)cur->content != (uintptr_t)(j - 1)) {
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
