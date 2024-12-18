#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <libft/ft_list.h>

char strs[6][6] = {
	"HeLLo",
	"wOrlD",
	"mY",
	"NaME",
	"iS",
	"SOta"
};

static t_list *make_list(size_t num) {
	t_list *head = NULL;
	for (size_t i = 0; i < num; i++) {
		t_list *node = ft_list_new(strs[rand() % 6]);
		ft_list_push_back(&head, node);
	}
	return head;
}

static void *id(void *content) {
	return content;
}

static void test(size_t num, void (*f)(void *)) {
	t_list *reserved = make_list(num);
	t_list *itered = ft_list_map(reserved, id, NULL);
	ft_list_iter(itered, f);

	size_t len = ft_list_size(reserved);
	if (len != ft_list_size(itered)) {
		fprintf(stderr, "ft_list_iter: different list size: %zu != %zu\n", len, ft_list_size(itered));
		ft_list_clear(&reserved, NULL);
		ft_list_clear(&itered, NULL);
		exit(1);
	}

	t_list *cur1 = reserved;
	t_list *cur2 = itered;
	for (size_t i = 0; i < len; i++, cur1 = cur1->next, cur2 = cur2->next) {
		f(cur1->content);
		char *expected = cur1->content;
		char *actual = cur2->content;
		if (strcmp(expected, actual) != 0) {
			fprintf(stderr, "ft_list_iter: different content: %s != %s\n", expected, actual);
			ft_list_clear(&reserved, NULL);
			ft_list_clear(&itered, NULL);
			exit(1);
		}
	}
	ft_list_clear(&reserved, NULL);
	ft_list_clear(&itered, NULL);
}

static void f(void *content) {
	char *str = content;
	for (size_t i = 0; str[i] != '\0'; i++) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			str[i] += 'a' - 'A';
		}
	}
}

int main(void) {
	for (size_t i = 0; i < 100; i++) {
		test(i, f);
	}
}
