#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libft/ft_list.h>

char strs[6][6] = {
	"Hello",
	"world",
	"My",
	"name",
	"is",
	"sota"
};

static t_list *make_list(size_t num) {
	t_list *head = NULL;
	for (size_t i = 0; i < num; i++) {
		t_list *node = ft_list_new(strs[rand() % 6]);
		ft_list_push_back(&head, node);
	}
	return head;
}

static void test(size_t num, void *(*f)(void *), void (*del)(void *)) {
	t_list *original = make_list(num);
	t_list *mapped = ft_list_map(original, f, del);

	size_t len = ft_list_size(original);
	if (len != ft_list_size(mapped)) {
		ft_list_clear(&original, NULL);
		ft_list_clear(&mapped, del);
		fprintf(stderr, "ft_list_map: different list size\n");
		exit(1);
	}

	t_list *cur_original = original;
	t_list *cur_mapped = mapped;
	for (size_t i = 0; i < len; i++, cur_original = cur_original->next, cur_mapped = cur_mapped->next) {
		char *expected = f(cur_original->content);
		char *actual = cur_mapped->content;
		if (strcmp(expected, actual) != 0) {
			fprintf(stderr, "ft_list_map: different content: %s != %s\n", expected, actual);
			del(expected);
			ft_list_clear(&original, NULL);
			ft_list_clear(&mapped, del);
			exit(1);
		}
		del(expected);
	}
	ft_list_clear(&original, NULL);
	ft_list_clear(&mapped, del);
}

static void *f(void *content) {
	return strdup((char *)content);
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		test(i, f, free);
	}
	return 0;
}
