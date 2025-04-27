#include <minishell/lexer.h>
#include <libft/ft_list.h>
#include <stdlib.h>
#include <stdio.h>

static char *token_name(t_token_id id) {
	if (id == TOKEN) {
		return "TOKEN";
	}
	if (id == WORD) {
		return "WORD";
	}
	if (id == ASSIGNMENT_WORD) {
		return "ASSIGNMENT WORD";
	}
	if (id == NAME) {
		return "NAME";
	}
	if (id == IO_NUMBER) {
		return "IO NUMBER";
	}
	if (id == PIPE) {
		return "PIPE";
	}
	if (id == LESS) {
		return "LESS";
	}
	if (id == GREAT) {
		return "GREAT";
	}
	if (id == DLESS) {
		return "DLESS";
	}
	if (id == DGREAT) {
		return "DGREAT";
	}
	if (id == LESSAND) {
		return "LESSAND";
	}
	if (id == GREATAND) {
		return "GREATAND";
	}
	return "Unknown";
}

static void test(const char *str) {
	printf("\nstr: %s\n", str);

	t_list *head = tokenize_input(str);
	t_list *cur = head;
	while (1) {
		t_token *token = (t_token *)cur->content;
		printf("Token: %s (%s)\n", token->str, token_name(token->id));
		free(token->str);
		cur = cur->next;
		if (cur == head) {
			break;
		}
	}
	ft_list_clear(&head, free);
}

int main(void) {
	test("echo hello world");
	test("echo \"hello world\"");
	test("echo 'hello world'");
	test("echo $USER");
	test("echo $USER | grep hello");
	test("echo hello > file.txt");
	test("echo hello >> file.txt");
	test("echo hello < file.txt");
	test("echo hello << file.txt");
	test("echo hello >& file.txt");
	test("echo hello <& file.txt");
	test("echo hello <&- file.txt");
	test("echo hello >&- file.txt");
	test("echo hello | grep hello | wc -l");
	test("echo hello | grep hello | wc -l > file.txt");
	test("echo hello | grep hello |");
	return 0;
}

