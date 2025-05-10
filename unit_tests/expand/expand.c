#include <libft/ft_string.h>
#include <minishell/expand.h>
#include <minishell/lexer.h>
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
        t_arg_list *cur = ast->args;
        while (1) {
            printf("%s", (char *)cur->content);
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

static void test(const char *cmd, const t_envp *envp) {
    t_token_list *start = tokenize_input(cmd);

    t_ast_node *ast = parse_tokens(start, start->prev);

    int parse_failed = check_parse_error(ast);
    free_tokens(start, parse_failed);
    if (parse_failed) {
        free_ast(ast, parse_failed);
        return;
    }

    expand_variables(ast, envp);
    printf("expanded variables:\n");
    printf("command: %s\n", cmd);
    print_ast(ast, 1);
    printf("\n");

    // split_field(ast, ft_getenv("IFS", envp));
    // printf("splitted field:\n");
    // printf("command: %s\n", cmd);
    // print_ast(ast, 1);
    // printf("\n");

    free_ast(ast, parse_failed);
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    const t_envp *env = make_ms_envp(envp);

    printf("\n");

    test("echo $HOME_sota", env);
    test("echo \"$HOME\"", env);
    test("echo '$HOME'", env);

    test("c'a't $USER_$USER_file.txt>file", env);
    test("echo \"$HOME\"_value > file", env);
    test("echo ''", env);

    free_ms_envp((t_envp *)env);
    return 0;
}
