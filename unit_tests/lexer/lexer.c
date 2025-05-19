#include <minishell/lexer.h>
#include <minishell/minishell.h>
#include <stdio.h>

static char *token_name(t_token_id id) {
    if (id == TOKEN) { return "TOKEN"; }
    if (id == PIPE) { return "PIPE"; }
    if (id == LESS) { return "LESS"; }
    if (id == GREAT) { return "GREAT"; }
    if (id == DLESS) { return "DLESS"; }
    if (id == DGREAT) { return "DGREAT"; }
    if (id == LESSAND) { return "LESSAND"; }
    if (id == GREATAND) { return "GREATAND"; }
    return "Unknown";
}

static void test(const char *str) {
    printf("\ncommand: [%s]\n", str);

    t_token_list *head;
    tokenize_input(&head, str);

    t_token_list *cur = head;
    while (1) {
        t_token *token = (t_token *)cur->content;
        printf("token: %s (%s)\n", token->str, token_name(token->id));
        cur = cur->next;
        if (cur == head) { break; }
    }
    free_tokens(head);
}

int main(void) {
    setbuf(stdout, NULL);
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
    test("c'a't $USER_$USER_file.txt>file");
    return 0;
}
