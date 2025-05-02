#include "minishell/lexer.h"
#include <minishell/parser.h>
#include <stdio.h>
#include <stdlib.h>

static char *token_name(t_token_id id) {
    if (id == TOKEN) { return "TOKEN"; }
    if (id == PIPE) { return "PIPE"; }
    if (id == LESS) { return "LESS"; }
    if (id == GREAT) { return "GREAT"; }
    if (id == DLESS) { return "DLESS"; }
    if (id == DGREAT) { return "DGREAT"; }
    if (id == LESSAND) { return "LESSAND"; }
    if (id == GREATAND) { return "GREATAND"; }
    if (id == COMMAND) { return "COMMAND"; }
    return "Unknown";
}

static void print_indent(int depth) {
    for (int i = 0; i < depth; i++)
        printf("    ");
}

void print_ast(t_ast_node *ast, int depth) {
    print_indent(depth);
    if (ast->id == PARSE_ERROR) {
        printf("parse error\n");
        return;
    }
    printf("token: %s\n", token_name(ast->id));
    if (ast->args != NULL) {
        print_indent(depth);
        printf("args: [");
        t_list *cur = ast->args;
        while (1) {
            char *str = ((t_token *)cur->content)->str;
            printf("%s", str);
            if (cur->next != ast->args) {
                printf(",");
            } else {
                printf("]\n");
            }
            cur = cur->next;
            if (cur == ast->args) { break; }
        }
    }
    if (ast->left != NULL) {
        print_indent(depth);
        printf("left:\n");
        print_ast(ast->left, depth + 1);
    }
    if (ast->right != NULL) {
        print_indent(depth);
        printf("right:\n");
        print_ast(ast->right, depth + 1);
    }
}

static void free_token(void *ptr) {
    t_token *token = (t_token *)ptr;
    free(token->str);
    free(token);
}

static void free_ast(t_ast_node *ast) {
    if (ast->left != NULL) { free_ast(ast->left); }
    if (ast->right != NULL) { free_ast(ast->right); }
    ft_list_clear(&ast->args, free_token);
    free(ast);
}

static void test(const char *cmd) {
    t_list *start = tokenize_input(cmd);

    t_ast_node *ast = parse_tokens(start, start->prev);
    ft_list_clear(&start, NULL);

    printf("command: %s\n", cmd);
    print_ast(ast, 0);
    printf("\n");
    free_ast(ast);
}

int main(void) {
    printf("\n");

    // pipe
    test("echo hello world");
    test("echo hello world | grep hello");
    test("echo hello world | grep hello | wc -l");

    // redirect
    test("echo hello world > file.txt");
    test("echo hello world < file.txt");
    test("echo hello world < file.txt > file2.txt");
    test("echo hello world < file.txt > file2.txt");
    test("echo hello world < file.txt > file2.txt > file3.txt");

    // quoted string
    test("echo \"hello world\"");
    test("echo 'hello world'");

    // environment variable
    test("echo $HOME");
    test("echo \"$HOME\"");
    test("echo '$HOME'");

    // parse error
    test("echo hello world |");
    test("echo hello world | | grep hello");
    test("echo hello world | grep hello |");
    test("echo hello world <");
    test("echo hello world >");

    // corner cases
    test("c'a't $USER_$USER_file.txt>file");
    return 0;
}
